from __future__ import annotations

import json
import sys
import tempfile
import unittest
from pathlib import Path


REPOSITORY_ROOT = Path(__file__).resolve().parents[1]
if str(REPOSITORY_ROOT) not in sys.path:
    sys.path.insert(0, str(REPOSITORY_ROOT))

from scripts.sync_discussion_data import (
    RATING_MARKER,
    aggregate_comments,
    aggregate_ratings,
    build_snapshot,
    parse_rating,
    write_snapshot,
)


def _rating(
    number: int,
    author: str,
    problem: str,
    difficulty: str,
    recommendation: str,
    updated_at: str,
) -> dict:
    return {
        "number": number,
        "title": f"[평가] {problem}",
        "url": f"https://github.com/example/repository/discussions/{number}",
        "createdAt": "2026-08-19T00:00:00Z",
        "updatedAt": updated_at,
        "author": {"login": author},
        "body": f"""{RATING_MARKER}

### 문제 식별자

{problem}

### 체감 난이도

{difficulty}

### 추천 여부

{recommendation}
""",
    }


class DiscussionDataTest(unittest.TestCase):
    def test_parse_rating_accepts_the_worker_discussion_shape(self) -> None:
        discussion = _rating(
            1, "octocat", "baekjoon/1000", "Gold III", "추천", "2026-08-20T00:00:00Z"
        )
        discussion["body"] = discussion["body"].replace(RATING_MARKER, "")
        parsed = parse_rating(discussion)

        self.assertIsNotNone(parsed)
        self.assertEqual(parsed["problem"], "baekjoon/1000")
        self.assertEqual(parsed["difficulty_value"], 13)
        self.assertEqual(parsed["recommendation"], "up")

    def test_parse_rating_rejects_untrusted_or_invalid_bodies(self) -> None:
        without_marker = _rating(
            1, "octocat", "baekjoon/1000", "Gold III", "추천", "2026-08-20T00:00:00Z"
        )
        without_marker["body"] = without_marker["body"].replace(RATING_MARKER, "")
        without_marker["title"] = "일반 Discussion"
        invalid_problem = _rating(
            2, "octocat", "../secret", "Gold III", "추천", "2026-08-20T00:00:00Z"
        )

        self.assertIsNone(parse_rating(without_marker))
        self.assertIsNone(parse_rating(invalid_problem))

    def test_rating_without_recommendation_still_counts_difficulty(self) -> None:
        result = aggregate_ratings(
            [
                _rating(
                    1,
                    "octocat",
                    "baekjoon/1000",
                    "Gold III",
                    "선택 안 함",
                    "2026-08-20T00:00:00Z",
                )
            ]
        )["baekjoon/1000"]

        self.assertEqual(result["difficulty"]["vote_count"], 1)
        self.assertIsNone(result["votes"][0]["recommendation"])
        self.assertNotIn("recommendation", result)

    def test_recommendation_percentage_uses_only_recommendation_votes(self) -> None:
        result = aggregate_ratings(
            [
                _rating(1, "octocat", "baekjoon/1000", "Gold III", "추천", "2026-08-20T00:00:00Z"),
                _rating(2, "hubot", "baekjoon/1000", "Gold III", "선택 안 함", "2026-08-20T01:00:00Z"),
            ]
        )["baekjoon/1000"]

        self.assertEqual(result["difficulty"]["vote_count"], 2)
        self.assertEqual(result["recommendation"]["recommended"], 1)
        self.assertEqual(result["recommendation"]["not_recommended"], 0)
        self.assertEqual(result["recommendation"]["recommended_percent"], 100)

    def test_latest_vote_per_github_user_wins(self) -> None:
        result = aggregate_ratings(
            [
                _rating(1, "octocat", "baekjoon/1000", "Bronze V", "비추천", "2026-08-19T00:00:00Z"),
                _rating(2, "octocat", "baekjoon/1000", "Gold I", "추천", "2026-08-20T00:00:00Z"),
                _rating(3, "hubot", "baekjoon/1000", "Gold III", "추천", "2026-08-20T01:00:00Z"),
            ]
        )["baekjoon/1000"]

        self.assertEqual(result["difficulty"]["vote_count"], 2)
        self.assertEqual(result["difficulty"]["mean_value"], 14.0)
        self.assertEqual(result["difficulty"]["representative"]["name"], "Gold II")
        self.assertEqual(result["recommendation"]["recommended"], 2)
        self.assertEqual([vote["author"] for vote in result["votes"]], ["hubot", "octocat"])

    def test_comments_are_mapped_from_term_or_problem_backlink(self) -> None:
        comments = aggregate_comments(
            [
                {
                    "number": 10,
                    "title": "problem:baekjoon/1000",
                    "body": "",
                    "url": "https://github.com/example/repository/discussions/10",
                    "updatedAt": "2026-08-20T00:00:00Z",
                    "comments": {"totalCount": 3},
                },
                {
                    "number": 11,
                    "title": "A problem discussion",
                    "body": "https://example.github.io/repo/problems/leetcode/1/",
                    "url": "https://github.com/example/repository/discussions/11",
                    "updatedAt": "2026-08-20T00:00:00Z",
                    "comments": {"totalCount": 2},
                },
            ]
        )

        self.assertEqual(comments["baekjoon/1000"]["comment_count"], 3)
        self.assertEqual(comments["leetcode/1"]["discussion_number"], 11)

    def test_snapshot_combines_comments_and_ratings(self) -> None:
        repository = {
            "id": "R_repo",
            "nameWithOwner": "example/repository",
            "url": "https://github.com/example/repository",
        }
        comments_category = {"id": "DIC_comments", "name": "Announcements", "slug": "announcements"}
        ratings_category = {"id": "DIC_ratings", "name": "General", "slug": "general"}
        snapshot = build_snapshot(
            repository,
            comments_category,
            ratings_category,
            [
                {
                    "number": 10,
                    "title": "problem:baekjoon/1000",
                    "body": "",
                    "url": "https://github.com/example/repository/discussions/10",
                    "updatedAt": "2026-08-20T00:00:00Z",
                    "comments": {"totalCount": 3},
                }
            ],
            [_rating(1, "octocat", "baekjoon/1000", "Gold III", "추천", "2026-08-20T00:00:00Z")],
        )

        self.assertTrue(snapshot["configuration"]["ready"])
        self.assertEqual(snapshot["summary"]["rating_count"], 1)
        self.assertEqual(snapshot["summary"]["comment_count"], 3)
        self.assertNotIn("rating_form_url", snapshot["configuration"])

    def test_unchanged_snapshot_preserves_generated_timestamp(self) -> None:
        with tempfile.TemporaryDirectory() as temporary_directory:
            path = Path(temporary_directory) / "snapshot.json"
            snapshot = {"schema_version": 1, "problems": {}}
            self.assertTrue(write_snapshot(path, dict(snapshot)))
            first = json.loads(path.read_text(encoding="utf-8"))

            self.assertFalse(write_snapshot(path, dict(snapshot)))
            second = json.loads(path.read_text(encoding="utf-8"))
            self.assertEqual(first["generated_at"], second["generated_at"])


if __name__ == "__main__":
    unittest.main()

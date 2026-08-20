from __future__ import annotations

import argparse
import json
import os
import re
import sys
from datetime import datetime, timezone
from pathlib import Path
from typing import Any
from urllib.error import HTTPError, URLError
from urllib.request import Request, urlopen


GRAPHQL_URL = "https://api.github.com/graphql"
SCHEMA_VERSION = 1
RATING_MARKER = "<!-- algorithm-solutions-rating:v1 -->"
RATING_TITLE_PREFIX = "[평가]"
PROBLEM_KEY_PATTERN = re.compile(r"^[a-z0-9-]+/[1-9][0-9]*$")
PROBLEM_TERM_PATTERN = re.compile(r"problem:([a-z0-9-]+/[1-9][0-9]*)", re.IGNORECASE)
PROBLEM_PATH_PATTERN = re.compile(
    r"/problems/([a-z0-9-]+)/([1-9][0-9]*)/", re.IGNORECASE
)


TIER_GROUPS = ("Bronze", "Silver", "Gold", "Platinum", "Diamond", "Ruby")
TIER_RANKS = ("V", "IV", "III", "II", "I")
TIER_NAMES = tuple(
    f"{group} {rank}" for group in TIER_GROUPS for rank in TIER_RANKS
)
TIER_VALUES = {name: index for index, name in enumerate(TIER_NAMES, start=1)}


class DiscussionSyncError(RuntimeError):
    pass


def _graphql(token: str, query: str, variables: dict[str, Any]) -> dict[str, Any]:
    request = Request(
        GRAPHQL_URL,
        data=json.dumps({"query": query, "variables": variables}).encode("utf-8"),
        headers={
            "Accept": "application/vnd.github+json",
            "Authorization": f"Bearer {token}",
            "Content-Type": "application/json",
            "User-Agent": "algorithm-solutions-discussion-sync",
            "X-GitHub-Api-Version": "2022-11-28",
        },
        method="POST",
    )
    try:
        with urlopen(request, timeout=30) as response:
            payload = json.load(response)
    except HTTPError as error:
        detail = error.read().decode("utf-8", errors="replace")
        raise DiscussionSyncError(
            f"GitHub GraphQL 요청 실패 ({error.code}): {detail}"
        ) from error
    except (URLError, TimeoutError, json.JSONDecodeError) as error:
        raise DiscussionSyncError(f"GitHub GraphQL 요청 실패: {error}") from error

    errors = payload.get("errors")
    if errors:
        messages = "; ".join(str(item.get("message", item)) for item in errors)
        raise DiscussionSyncError(f"GitHub GraphQL 오류: {messages}")
    data = payload.get("data")
    if not isinstance(data, dict):
        raise DiscussionSyncError("GitHub GraphQL 응답에 data가 없습니다.")
    return data


def _repository_metadata(
    token: str, owner: str, name: str
) -> tuple[dict[str, Any], list[dict[str, Any]]]:
    query = """
    query RepositoryMetadata($owner: String!, $name: String!) {
      repository(owner: $owner, name: $name) {
        id
        nameWithOwner
        url
        discussionCategories(first: 100) {
          nodes {
            id
            name
            slug
          }
        }
      }
    }
    """
    repository = _graphql(token, query, {"owner": owner, "name": name}).get("repository")
    if not isinstance(repository, dict):
        raise DiscussionSyncError(f"저장소를 찾을 수 없습니다: {owner}/{name}")
    categories = repository.get("discussionCategories", {}).get("nodes", [])
    if not isinstance(categories, list):
        raise DiscussionSyncError("Discussion 카테고리 응답 형식이 올바르지 않습니다.")
    return repository, [item for item in categories if isinstance(item, dict)]


def _category_by_name(
    categories: list[dict[str, Any]], category_name: str
) -> dict[str, Any]:
    for category in categories:
        if str(category.get("name", "")).casefold() == category_name.casefold():
            return category
    available = ", ".join(str(item.get("name")) for item in categories) or "없음"
    raise DiscussionSyncError(
        f"Discussion 카테고리 '{category_name}'를 찾을 수 없습니다. 현재 카테고리: {available}"
    )


def _category_discussions(
    token: str,
    owner: str,
    name: str,
    category_id: str,
) -> list[dict[str, Any]]:
    query = """
    query CategoryDiscussions(
      $owner: String!
      $name: String!
      $categoryId: ID!
      $after: String
    ) {
      repository(owner: $owner, name: $name) {
        discussions(
          first: 100
          after: $after
          categoryId: $categoryId
          orderBy: {field: UPDATED_AT, direction: DESC}
        ) {
          nodes {
            number
            title
            body
            url
            createdAt
            updatedAt
            author {
              login
            }
            comments {
              totalCount
            }
          }
          pageInfo {
            hasNextPage
            endCursor
          }
        }
      }
    }
    """
    discussions: list[dict[str, Any]] = []
    after: str | None = None
    while True:
        data = _graphql(
            token,
            query,
            {
                "owner": owner,
                "name": name,
                "categoryId": category_id,
                "after": after,
            },
        )
        repository = data.get("repository")
        if not isinstance(repository, dict):
            raise DiscussionSyncError(f"저장소를 찾을 수 없습니다: {owner}/{name}")
        connection = repository.get("discussions")
        if not isinstance(connection, dict):
            raise DiscussionSyncError("Discussion 목록 응답 형식이 올바르지 않습니다.")
        nodes = connection.get("nodes", [])
        discussions.extend(item for item in nodes if isinstance(item, dict))
        page_info = connection.get("pageInfo", {})
        if not page_info.get("hasNextPage"):
            break
        after = page_info.get("endCursor")
        if not after:
            raise DiscussionSyncError("Discussion 페이지 커서가 비어 있습니다.")
    return discussions


def _form_field(body: str, label: str) -> str | None:
    pattern = re.compile(
        rf"^###\s+{re.escape(label)}\s*$\n+(.*?)(?=\n+###\s|\Z)",
        re.MULTILINE | re.DOTALL,
    )
    match = pattern.search(body)
    if not match:
        return None
    value = match.group(1).strip().strip("`").strip()
    if not value or value == "_No response_":
        return None
    return value


def parse_rating(discussion: dict[str, Any]) -> dict[str, Any] | None:
    body = str(discussion.get("body", ""))
    title = str(discussion.get("title", "")).strip()
    if RATING_MARKER not in body and not title.startswith(RATING_TITLE_PREFIX):
        return None

    problem_key = (_form_field(body, "문제 식별자") or "").casefold()
    difficulty = _form_field(body, "체감 난이도") or ""
    recommendation = _form_field(body, "추천 여부") or "선택 안 함"
    author = discussion.get("author")
    login = str(author.get("login", "")).strip() if isinstance(author, dict) else ""
    if not PROBLEM_KEY_PATTERN.fullmatch(problem_key):
        return None
    if difficulty not in TIER_VALUES:
        return None
    if recommendation not in {"추천", "비추천", "선택 안 함"}:
        return None
    if not login:
        return None

    return {
        "problem": problem_key,
        "author": login,
        "difficulty": difficulty,
        "difficulty_value": TIER_VALUES[difficulty],
        "recommendation": (
            "up" if recommendation == "추천"
            else "down" if recommendation == "비추천"
            else None
        ),
        "discussion_number": int(discussion.get("number", 0)),
        "discussion_url": str(discussion.get("url", "")),
        "created_at": str(discussion.get("createdAt", "")),
        "updated_at": str(discussion.get("updatedAt", "")),
    }


def _problem_key_from_comment_discussion(discussion: dict[str, Any]) -> str | None:
    searchable = f"{discussion.get('title', '')}\n{discussion.get('body', '')}"
    term_match = PROBLEM_TERM_PATTERN.search(searchable)
    if term_match:
        return term_match.group(1).casefold()
    path_match = PROBLEM_PATH_PATTERN.search(searchable)
    if path_match:
        return f"{path_match.group(1)}/{path_match.group(2)}".casefold()
    return None


def _latest_ratings(discussions: list[dict[str, Any]]) -> list[dict[str, Any]]:
    latest: dict[tuple[str, str], dict[str, Any]] = {}
    for discussion in discussions:
        rating = parse_rating(discussion)
        if rating is None:
            continue
        key = (rating["problem"], rating["author"].casefold())
        previous = latest.get(key)
        order = (rating["updated_at"], rating["discussion_number"])
        if previous is None or order > (
            previous["updated_at"],
            previous["discussion_number"],
        ):
            latest[key] = rating
    return sorted(
        latest.values(),
        key=lambda item: (item["problem"], item["author"].casefold()),
    )


def _tier_slug(tier_name: str) -> str:
    return tier_name.split(" ", 1)[0].casefold()


def aggregate_ratings(
    discussions: list[dict[str, Any]],
) -> dict[str, dict[str, Any]]:
    grouped: dict[str, list[dict[str, Any]]] = {}
    for rating in _latest_ratings(discussions):
        grouped.setdefault(rating["problem"], []).append(rating)

    aggregates: dict[str, dict[str, Any]] = {}
    for problem_key, votes in sorted(grouped.items()):
        vote_count = len(votes)
        mean_value = sum(item["difficulty_value"] for item in votes) / vote_count
        representative_value = min(30, max(1, int(mean_value + 0.5)))
        representative_name = TIER_NAMES[representative_value - 1]
        distribution = {
            tier_name: sum(item["difficulty"] == tier_name for item in votes)
            for tier_name in TIER_NAMES
        }
        distribution = {name: count for name, count in distribution.items() if count}
        recommendation_votes = [
            item for item in votes if item["recommendation"] in {"up", "down"}
        ]
        recommended = sum(item["recommendation"] == "up" for item in recommendation_votes)
        not_recommended = len(recommendation_votes) - recommended
        aggregates[problem_key] = {
            "difficulty": {
                "vote_count": vote_count,
                "mean_value": round(mean_value, 2),
                "representative": {
                    "value": representative_value,
                    "name": representative_name,
                    "group": _tier_slug(representative_name),
                },
                "distribution": distribution,
            },
            "votes": votes,
        }
        if recommendation_votes:
            aggregates[problem_key]["recommendation"] = {
                "recommended": recommended,
                "not_recommended": not_recommended,
                "score": recommended - not_recommended,
                "recommended_percent": round(recommended * 100 / len(recommendation_votes)),
            }
    return aggregates


def aggregate_comments(
    discussions: list[dict[str, Any]],
) -> dict[str, dict[str, Any]]:
    comments: dict[str, dict[str, Any]] = {}
    for discussion in discussions:
        problem_key = _problem_key_from_comment_discussion(discussion)
        if problem_key is None:
            continue
        item = {
            "discussion_number": int(discussion.get("number", 0)),
            "discussion_url": str(discussion.get("url", "")),
            "comment_count": int(discussion.get("comments", {}).get("totalCount", 0)),
            "updated_at": str(discussion.get("updatedAt", "")),
        }
        previous = comments.get(problem_key)
        if previous is None or (item["updated_at"], item["discussion_number"]) > (
            previous["updated_at"],
            previous["discussion_number"],
        ):
            comments[problem_key] = item
    return dict(sorted(comments.items()))


def build_snapshot(
    repository: dict[str, Any],
    comments_category: dict[str, Any],
    ratings_category: dict[str, Any],
    comment_discussions: list[dict[str, Any]],
    rating_discussions: list[dict[str, Any]],
) -> dict[str, Any]:
    repository_name = str(repository["nameWithOwner"])
    ratings = aggregate_ratings(rating_discussions)
    comments = aggregate_comments(comment_discussions)
    problems: dict[str, dict[str, Any]] = {}
    for problem_key in sorted(set(ratings) | set(comments)):
        problems[problem_key] = {
            **ratings.get(problem_key, {}),
            "comments": comments.get(
                problem_key,
                {"comment_count": 0, "discussion_url": None},
            ),
        }

    return {
        "schema_version": SCHEMA_VERSION,
        "repository": repository_name,
        "configuration": {
            "repository_id": str(repository["id"]),
            "comments_category": {
                "id": str(comments_category["id"]),
                "name": str(comments_category["name"]),
                "slug": str(comments_category["slug"]),
            },
            "ratings_category": {
                "id": str(ratings_category["id"]),
                "name": str(ratings_category["name"]),
                "slug": str(ratings_category["slug"]),
            },
            "ready": True,
        },
        "summary": {
            "problem_count": len(problems),
            "rating_count": sum(len(item.get("votes", [])) for item in problems.values()),
            "comment_count": sum(
                item.get("comments", {}).get("comment_count", 0)
                for item in problems.values()
            ),
        },
        "problems": problems,
    }


def write_snapshot(path: Path, snapshot: dict[str, Any]) -> bool:
    previous: dict[str, Any] | None = None
    if path.is_file():
        try:
            loaded = json.loads(path.read_text(encoding="utf-8"))
            if isinstance(loaded, dict):
                previous = loaded
        except (OSError, json.JSONDecodeError):
            previous = None

    comparable_previous = dict(previous or {})
    previous_generated_at = comparable_previous.pop("generated_at", None)
    if comparable_previous == snapshot and previous_generated_at:
        snapshot["generated_at"] = previous_generated_at
        changed = False
    else:
        snapshot["generated_at"] = datetime.now(timezone.utc).isoformat(
            timespec="seconds"
        ).replace("+00:00", "Z")
        changed = True

    rendered = json.dumps(snapshot, ensure_ascii=False, indent=2) + "\n"
    if not path.is_file() or path.read_text(encoding="utf-8") != rendered:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(rendered, encoding="utf-8")
    return changed


def sync(
    repository_name: str,
    token: str,
    comments_category_name: str,
    ratings_category_name: str,
) -> dict[str, Any]:
    parts = repository_name.split("/", 1)
    if len(parts) != 2 or not all(parts):
        raise DiscussionSyncError(
            f"저장소 이름은 owner/name 형식이어야 합니다: {repository_name}"
        )
    owner, name = parts
    repository, categories = _repository_metadata(token, owner, name)
    comments_category = _category_by_name(categories, comments_category_name)
    ratings_category = _category_by_name(categories, ratings_category_name)
    comment_discussions = _category_discussions(
        token, owner, name, str(comments_category["id"])
    )
    rating_discussions = _category_discussions(
        token, owner, name, str(ratings_category["id"])
    )
    return build_snapshot(
        repository,
        comments_category,
        ratings_category,
        comment_discussions,
        rating_discussions,
    )


def _arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="GitHub Discussions 댓글과 문제 평가를 정적 JSON으로 동기화"
    )
    parser.add_argument("--repository", default=os.environ.get("GITHUB_REPOSITORY"))
    parser.add_argument("--output", type=Path, default=Path("community-data/discussions.json"))
    parser.add_argument("--comments-category", default="Announcements")
    parser.add_argument("--ratings-category", default="General")
    return parser.parse_args()


def main() -> int:
    args = _arguments()
    token = os.environ.get("GH_TOKEN") or os.environ.get("GITHUB_TOKEN")
    if not args.repository:
        print("--repository 또는 GITHUB_REPOSITORY가 필요합니다.", file=sys.stderr)
        return 2
    if not token:
        print("GH_TOKEN 또는 GITHUB_TOKEN이 필요합니다.", file=sys.stderr)
        return 2

    try:
        snapshot = sync(
            args.repository,
            token,
            args.comments_category,
            args.ratings_category,
        )
        changed = write_snapshot(args.output, snapshot)
    except (DiscussionSyncError, OSError, ValueError) as error:
        print(f"Discussion sync failed: {error}", file=sys.stderr)
        return 1

    state = "변경됨" if changed else "변경 없음"
    print(
        f"Discussion 데이터 동기화 완료 ({state}): "
        f"{snapshot['summary']['problem_count']}개 문제, "
        f"{snapshot['summary']['rating_count']}개 평가, "
        f"{snapshot['summary']['comment_count']}개 댓글"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

from __future__ import annotations

import tempfile
import unittest
from pathlib import Path

import yaml

from scripts.update_leetcode_problems import (
    LeetCodeUpdateError,
    parse_catalog,
    update_config,
)


def _payload(*rows: tuple[int, str, str, bool]) -> dict:
    return {
        "stat_status_pairs": [
            {
                "paid_only": paid_only,
                "stat": {
                    "frontend_question_id": problem_id,
                    "question__title": title,
                    "question__title_slug": slug,
                }
            }
            for problem_id, title, slug, paid_only in rows
        ]
    }


class UpdateLeetCodeProblemsTest(unittest.TestCase):
    def setUp(self) -> None:
        self.temporary_directory = tempfile.TemporaryDirectory()
        self.root = Path(self.temporary_directory.name)
        self.config_path = self.root / "pages" / "config.yaml"
        self.config_path.parent.mkdir()
        self.config_path.write_text(
            """site:
  title: Test
problems:
  leetcode/9:
    title: Old title
    url: https://example.com/old
  hackerrank/8137:
    title: Select All
    url: https://www.hackerrank.com/challenges/select-all-sql/problem
""",
            encoding="utf-8",
        )

    def tearDown(self) -> None:
        self.temporary_directory.cleanup()

    def test_updates_every_free_problem_and_preserves_other_platforms(self) -> None:
        catalog = parse_catalog(
            _payload(
                (1, "Two Sum", "two-sum", False),
                (2, "Add Two Numbers", "add-two-numbers", True),
                (9, "Palindrome Number", "palindrome-number", False),
                (42, "Trapping Rain Water", "trapping-rain-water", False),
            )
        )

        result = update_config(self.config_path, catalog)

        self.assertTrue(result.changed)
        self.assertEqual(result.problem_count, 3)
        config = yaml.safe_load(self.config_path.read_text(encoding="utf-8"))
        self.assertEqual(config["problems"]["leetcode/1"]["title"], "Two Sum")
        self.assertEqual(
            config["problems"]["leetcode/9"],
            {
                "title": "Palindrome Number",
                "url": "https://leetcode.com/problems/palindrome-number/",
            },
        )
        self.assertEqual(
            config["problems"]["leetcode/42"]["title"],
            "Trapping Rain Water",
        )
        self.assertNotIn("leetcode/2", config["problems"])
        self.assertEqual(config["problems"]["hackerrank/8137"]["title"], "Select All")
        self.assertFalse(update_config(self.config_path, catalog, check=True).changed)

    def test_rejects_catalog_containing_only_premium_problems(self) -> None:
        with self.assertRaisesRegex(LeetCodeUpdateError, "유효한 문제 정보"):
            parse_catalog(_payload((2, "Add Two Numbers", "add-two-numbers", True)))

    def test_rejects_conflicting_duplicate_problem_ids(self) -> None:
        with self.assertRaisesRegex(LeetCodeUpdateError, "중복"):
            parse_catalog(
                _payload(
                    (9, "Palindrome Number", "palindrome-number", False),
                    (9, "Different", "different", False),
                )
            )


if __name__ == "__main__":
    unittest.main()

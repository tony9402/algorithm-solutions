from __future__ import annotations

import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from io import StringIO
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch


REPOSITORY_ROOT = Path(__file__).resolve().parents[1]
if str(REPOSITORY_ROOT) not in sys.path:
    sys.path.insert(0, str(REPOSITORY_ROOT))

from scripts.validate_solution_pr import (
    COMMENT_MARKER,
    Change,
    get_git_changes,
    get_merge_base,
    get_worktree_changes,
    render_pr_comment,
    validate_changes,
)
from scripts.precheck import validate_local_solutions


CANONICAL_CPP = """// Authored by: contributor
// Co-authored by: -
// Link: https://www.acmicpc.net/source/1

int main() { return 0; }

/* Solution Description
상수 시간에 답을 구한다.
*/
"""


class SolutionPullRequestValidatorTest(unittest.TestCase):
    def setUp(self) -> None:
        self.temporary_directory = tempfile.TemporaryDirectory()
        self.root = Path(self.temporary_directory.name)
        config_path = self.root / "pages" / "config.yaml"
        config_path.parent.mkdir(parents=True)
        config_path.write_text(
            """platforms:
  baekjoon:
    label: Baekjoon
    problem_url_template: https://www.acmicpc.net/problem/{problem_id}
  leetcode:
    label: LeetCode
problems: {}
""",
            encoding="utf-8",
        )

    def tearDown(self) -> None:
        self.temporary_directory.cleanup()

    def _write(self, relative_path: str, content: str = CANONICAL_CPP) -> None:
        path = self.root / relative_path
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(content, encoding="utf-8")

    def test_accepts_one_solution_with_related_files(self) -> None:
        path = "solutions/baekjoon/1000/main.cpp"
        self._write(path)

        report = validate_changes(
            self.root,
            [Change("A", path), Change("M", "pages/config.yaml"), Change("M", "README.md")],
        )

        self.assertTrue(report.valid, [item.format() for item in report.errors])
        self.assertEqual(report.changed_solution_files, [path])
        self.assertEqual(report.problem["url"], "https://www.acmicpc.net/problem/1000")

    def test_rejects_more_than_one_solution(self) -> None:
        first = "solutions/baekjoon/1000/main.cpp"
        second = "solutions/baekjoon/1001/main.cpp"
        self._write(first)
        self._write(second)

        report = validate_changes(self.root, [Change("A", first), Change("A", second)])

        self.assertFalse(report.valid)
        self.assertTrue(any(item.code == "PR001" for item in report.errors))

    def test_rejects_deleted_solution(self) -> None:
        report = validate_changes(
            self.root, [Change("D", "solutions/baekjoon/1000/main.cpp")]
        )

        self.assertFalse(report.valid)
        self.assertTrue(any(item.code == "PR002" for item in report.errors))

    def test_rejects_missing_description_in_changed_solution(self) -> None:
        path = "solutions/baekjoon/1000/main.cpp"
        self._write(
            path,
            "// Authored by: contributor\n\nint main() { return 0; }\n",
        )

        report = validate_changes(self.root, [Change("M", path)])

        self.assertFalse(report.valid)
        self.assertTrue(any(item.code == "SOL007" for item in report.errors))

    def test_accepts_empty_description_block(self) -> None:
        path = "solutions/baekjoon/1000/main.cpp"
        self._write(
            path,
            CANONICAL_CPP.replace("상수 시간에 답을 구한다.\n", ""),
        )

        report = validate_changes(self.root, [Change("M", path)])

        self.assertTrue(report.valid, [item.format() for item in report.errors])
        assert report.solution is not None
        self.assertFalse(report.solution["has_solution_description"])

    def test_rejects_unsafe_submission_url(self) -> None:
        path = "solutions/baekjoon/1000/main.cpp"
        self._write(
            path,
            CANONICAL_CPP.replace(
                "https://www.acmicpc.net/source/1",
                "javascript:alert(1)",
            ),
        )

        report = validate_changes(self.root, [Change("A", path)])

        self.assertFalse(report.valid)
        self.assertTrue(any(item.code == "SOL005" for item in report.errors))

    def test_requires_leetcode_problem_override_without_submission_link(self) -> None:
        path = "solutions/leetcode/9/main.cpp"
        self._write(path, CANONICAL_CPP.replace("https://www.acmicpc.net/source/1", ""))

        report = validate_changes(self.root, [Change("A", path)])

        self.assertFalse(report.valid)
        self.assertTrue(any(item.code == "PR004" for item in report.errors))

    def test_reads_added_solution_from_git_diff(self) -> None:
        path = "solutions/baekjoon/1000/main.cpp"
        self._write(path)
        completed = SimpleNamespace(stdout=f"A\0{path}\0".encode(), stderr=b"")
        with patch("scripts.validate_solution_pr.subprocess.run", return_value=completed):
            changes = get_git_changes(self.root, "base-sha", "head-sha")
        report = validate_changes(self.root, changes)

        self.assertEqual(changes, [Change("A", path)])
        self.assertTrue(report.valid, [item.format() for item in report.errors])

    def test_reads_tracked_and_untracked_worktree_changes(self) -> None:
        tracked_path = "README.md"
        untracked_path = "solutions/baekjoon/1000/main.cpp"
        responses = [
            SimpleNamespace(stdout=b"base-sha\n", stderr=b""),
            SimpleNamespace(stdout=f"M\0{tracked_path}\0".encode(), stderr=b""),
            SimpleNamespace(stdout=f"{untracked_path}\0".encode(), stderr=b""),
        ]
        with patch("scripts.validate_solution_pr.subprocess.run", side_effect=responses):
            base_sha = get_merge_base(self.root, "origin/main")
            changes = get_worktree_changes(self.root, base_sha)

        self.assertEqual(base_sha, "base-sha")
        self.assertEqual(
            changes,
            [Change("M", tracked_path), Change("A", untracked_path)],
        )

    def test_local_precheck_accepts_multiple_changed_solutions(self) -> None:
        first = "solutions/baekjoon/1000/main.cpp"
        second = "solutions/baekjoon/1001/main.cpp"
        self._write(first)
        self._write(second)

        config = {
            "platforms": {
                "baekjoon": {
                    "label": "Baekjoon",
                    "problem_url_template": "https://www.acmicpc.net/problem/{problem_id}",
                }
            },
            "problems": {},
        }
        with (
            patch("scripts.precheck.load_config", return_value=config) as preload_config,
            patch("scripts.validate_solution_pr.load_config") as per_file_load_config,
            redirect_stdout(StringIO()),
        ):
            valid = validate_local_solutions(
                self.root,
                [Change("A", first), Change("A", second)],
            )

        self.assertTrue(valid)
        preload_config.assert_called_once_with(self.root / "pages" / "config.yaml")
        per_file_load_config.assert_not_called()

    def test_renders_success_comment(self) -> None:
        path = "solutions/baekjoon/1000/main.cpp"
        self._write(path)
        report = validate_changes(self.root, [Change("A", path)])

        comment = render_pr_comment(report, "https://github.com/example/repo/actions/runs/1")

        self.assertTrue(comment.startswith(COMMENT_MARKER))
        self.assertIn("솔루션 형식 검사 통과", comment)
        self.assertIn("오류 | 0개", comment)
        self.assertIn("Actions 검사 실행 보기", comment)

    def test_renders_failure_comment_with_escaped_diagnostic(self) -> None:
        path = "solutions/baekjoon/1000/main.cpp"
        self._write(path, "// Authored by: <img src=x>\n")
        report = validate_changes(self.root, [Change("M", path)])

        comment = render_pr_comment(report)

        self.assertIn("솔루션 형식 검사 실패", comment)
        self.assertIn("상세 결과", comment)
        self.assertNotIn("<img", comment)
        self.assertIn("&lt;img", comment)


if __name__ == "__main__":
    unittest.main()

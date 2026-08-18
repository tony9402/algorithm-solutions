from __future__ import annotations

import sys
import tempfile
import unittest
from pathlib import Path


REPOSITORY_ROOT = Path(__file__).resolve().parents[1]
if str(REPOSITORY_ROOT) not in sys.path:
    sys.path.insert(0, str(REPOSITORY_ROOT))

from scripts.solution_parser import LANGUAGE_SPECS, parse_metadata_lines, parse_solution


FIXTURE_ROOT = REPOSITORY_ROOT / "tests" / "fixtures"


class SolutionParserTest(unittest.TestCase):
    def test_parses_canonical_cpp_in_strict_mode(self) -> None:
        result = parse_solution(
            Path("solutions/baekjoon/1000/main.cpp"), FIXTURE_ROOT, mode="strict"
        )

        self.assertTrue(result.valid, [item.format() for item in result.errors])
        self.assertIsNotNone(result.solution)
        solution = result.solution
        assert solution is not None
        self.assertEqual(solution.author, "test-author")
        self.assertEqual(solution.coauthors, ["reviewer", "maintainer"])
        self.assertEqual(solution.language, "C++")
        self.assertIn("std::cout", solution.code)
        self.assertNotIn("Authored by", solution.code)
        self.assertNotIn("Solution Description", solution.code)
        self.assertEqual(solution.solution_description, "두 수를 입력받아 합을 출력한다.")

    def test_optional_metadata_is_allowed(self) -> None:
        result = parse_solution(
            Path("solutions/baekjoon/1001/main.py"), FIXTURE_ROOT, mode="strict"
        )

        self.assertTrue(result.valid, [item.format() for item in result.errors])
        assert result.solution is not None
        self.assertEqual(result.solution.coauthors, [])
        self.assertIsNone(result.solution.submission_url)

    def test_legacy_header_warns_in_compat_and_fails_in_strict(self) -> None:
        path = Path("solutions/baekjoon/1002/main.py")
        compatible = parse_solution(path, FIXTURE_ROOT, mode="compat")
        strict = parse_solution(path, FIXTURE_ROOT, mode="strict")

        self.assertTrue(compatible.valid)
        self.assertTrue(any(item.code == "SOL004" for item in compatible.warnings))
        self.assertTrue(any(item.code == "SOL004" for item in strict.errors))

    def test_unterminated_description_is_an_error(self) -> None:
        result = parse_solution(
            Path("solutions/baekjoon/1003/main.py"), FIXTURE_ROOT, mode="strict"
        )

        self.assertFalse(result.valid)
        self.assertTrue(any(item.code == "SOL006" for item in result.errors))

    def test_marker_inside_code_string_is_not_a_description(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path = root / "solutions" / "baekjoon" / "1004" / "main.py"
            path.parent.mkdir(parents=True)
            path.write_text(
                '# Authored by: author\n\nprint("Solution Description")\n',
                encoding="utf-8",
            )

            result = parse_solution(path, root, mode="compat")

        self.assertTrue(result.valid)
        assert result.solution is not None
        self.assertIn("Solution Description", result.solution.code)
        self.assertIsNone(result.solution.solution_description)

    def test_legacy_metadata_adapter(self) -> None:
        metadata = parse_metadata_lines(
            [
                "# // Authored by : legacy\n",
                "# // Co-authored by : -\n",
                "# // Link : http://boj.kr/value\n",
            ]
        )
        self.assertEqual(metadata["Authored by"], "legacy")
        self.assertEqual(metadata["Co-authored by"], "-")
        self.assertEqual(metadata["Link"], "http://boj.kr/value")

    def test_all_ten_allowed_languages_accept_empty_description_in_strict_mode(self) -> None:
        self.assertEqual(len(LANGUAGE_SPECS), 10)
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            for index, spec in enumerate(LANGUAGE_SPECS.values(), start=2000):
                stem = "Main" if spec.extension == "java" else "main"
                path = root / "solutions" / "baekjoon" / str(index) / f"{stem}.{spec.extension}"
                path.parent.mkdir(parents=True)
                if spec.description_kind == "python":
                    description = '""" Solution Description\n"""\n'
                else:
                    description = "/* Solution Description\n*/\n"
                code = "SELECT 1;" if spec.extension == "sql" else "solution code"
                path.write_text(
                    f"{spec.line_comment} Authored by: author\n\n{code}\n\n{description}",
                    encoding="utf-8",
                )

                result = parse_solution(path, root, mode="strict")

                self.assertTrue(
                    result.valid,
                    f"{spec.language}: {[item.format() for item in result.errors]}",
                )
                assert result.solution is not None
                self.assertIsNone(result.solution.solution_description)

    def test_repository_baseline_parses_without_errors(self) -> None:
        paths = sorted((REPOSITORY_ROOT / "solutions").glob("*/*/*"))
        results = [
            parse_solution(path, REPOSITORY_ROOT, mode="compat")
            for path in paths
            if path.is_file() or path.is_symlink()
        ]
        errors = [item.format() for result in results for item in result.errors]
        problems = {
            (result.solution.platform, result.solution.problem_id)
            for result in results
            if result.solution is not None
        }

        self.assertGreaterEqual(len(results), 549)
        self.assertGreaterEqual(len(problems), 427)
        self.assertEqual(errors, [])


if __name__ == "__main__":
    unittest.main()

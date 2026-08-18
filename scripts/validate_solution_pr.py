from __future__ import annotations

import argparse
import html
import json
import os
import subprocess
import sys
from dataclasses import asdict, dataclass, field
from pathlib import Path
from urllib.parse import urlsplit


TRUSTED_REPOSITORY_ROOT = Path(__file__).resolve().parents[1]
if str(TRUSTED_REPOSITORY_ROOT) not in sys.path:
    sys.path.insert(0, str(TRUSTED_REPOSITORY_ROOT))

from pages.problem_catalog import CatalogError, load_config, resolve_problem
from scripts.solution_parser import Diagnostic, ParsedSolution, parse_solution


COMMENT_MARKER = "<!-- solution-format-report -->"


@dataclass(frozen=True)
class Change:
    status: str
    path: str
    old_path: str | None = None


@dataclass
class ValidationReport:
    valid: bool = False
    pr_number: int | None = None
    changed_solution_files: list[str] = field(default_factory=list)
    solution: dict[str, object] | None = None
    problem: dict[str, object] | None = None
    errors: list[Diagnostic] = field(default_factory=list)
    warnings: list[Diagnostic] = field(default_factory=list)

    def as_dict(self) -> dict[str, object]:
        return {
            "valid": self.valid,
            "pr_number": self.pr_number,
            "changed_solution_files": self.changed_solution_files,
            "solution": self.solution,
            "problem": self.problem,
            "errors": [item.as_dict() for item in self.errors],
            "warnings": [item.as_dict() for item in self.warnings],
        }


def _is_solution_path(path: str | None) -> bool:
    return bool(path) and (path == "solutions" or path.startswith("solutions/"))


def get_git_changes(repository_root: Path, base_sha: str, head_sha: str) -> list[Change]:
    command = [
        "git",
        "diff",
        "--name-status",
        "--find-renames",
        "-z",
        f"{base_sha}...{head_sha}",
    ]
    completed = subprocess.run(
        command,
        cwd=repository_root,
        check=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    fields = completed.stdout.decode("utf-8").split("\0")
    changes: list[Change] = []
    index = 0
    while index < len(fields) and fields[index]:
        status = fields[index]
        index += 1
        if status.startswith(("R", "C")):
            old_path = fields[index]
            new_path = fields[index + 1]
            index += 2
            changes.append(Change(status=status[0], path=new_path, old_path=old_path))
        else:
            path = fields[index]
            index += 1
            changes.append(Change(status=status[0], path=path))
    return changes


def _report_diagnostic(
    target: list[Diagnostic],
    code: str,
    message: str,
    path: str = "solutions",
    line: int | None = None,
    severity: str = "error",
) -> None:
    target.append(
        Diagnostic(
            code=code,
            severity="warning" if severity == "warning" else "error",
            message=message,
            path=path,
            line=line,
        )
    )


def _normalised_solution(solution: ParsedSolution) -> dict[str, object]:
    data = solution.as_dict()
    data.pop("code", None)
    data.pop("solution_description", None)
    data["has_solution_description"] = bool(solution.solution_description)
    return data


def validate_changes(
    repository_root: Path,
    changes: list[Change],
    config_path: Path | None = None,
) -> ValidationReport:
    report = ValidationReport()
    solution_changes = [
        change
        for change in changes
        if _is_solution_path(change.path) or _is_solution_path(change.old_path)
    ]

    deleted = [change for change in solution_changes if change.status == "D"]
    moved_out = [
        change
        for change in solution_changes
        if change.status == "R" and not _is_solution_path(change.path)
    ]
    if deleted or moved_out:
        for change in deleted + moved_out:
            _report_diagnostic(
                report.errors,
                "PR002",
                (
                    "솔루션 삭제 또는 solutions 밖으로의 이동은 "
                    "maintainer 절차가 필요합니다."
                ),
                change.old_path or change.path,
            )

    candidates = [
        change
        for change in solution_changes
        if change.status in {"A", "C", "M", "R"} and _is_solution_path(change.path)
    ]
    report.changed_solution_files = [change.path for change in candidates]
    if len(candidates) != 1:
        _report_diagnostic(
            report.errors,
            "PR001",
            (
                "하나의 PR에는 추가·수정된 솔루션 파일이 정확히 "
                f"1개여야 합니다(현재 {len(candidates)}개)."
            ),
        )
        report.valid = False
        return report

    candidate = candidates[0]
    parse_result = parse_solution(Path(candidate.path), repository_root, mode="strict")
    report.errors.extend(parse_result.errors)
    report.warnings.extend(parse_result.warnings)
    if parse_result.solution is None:
        report.valid = False
        return report

    solution = parse_result.solution
    report.solution = _normalised_solution(solution)
    resolved_config_path = config_path or repository_root / "pages" / "config.yaml"
    try:
        config = load_config(resolved_config_path)
        problem = resolve_problem(
            config,
            solution.platform,
            solution.problem_id,
            [solution.submission_url],
        )
        report.problem = asdict(problem)
    except (CatalogError, OSError, ValueError) as error:
        _report_diagnostic(
            report.errors,
            "PR004",
            str(error),
            resolved_config_path.relative_to(repository_root).as_posix()
            if resolved_config_path.is_relative_to(repository_root)
            else str(resolved_config_path),
        )

    report.valid = not report.errors
    return report


def _escape_workflow_command(value: str) -> str:
    return value.replace("%", "%25").replace("\r", "%0D").replace("\n", "%0A")


def emit_annotations(report: ValidationReport) -> None:
    for diagnostic in [*report.errors, *report.warnings]:
        command = "error" if diagnostic.severity == "error" else "warning"
        properties = [f"file={_escape_workflow_command(diagnostic.path)}"]
        if diagnostic.line is not None:
            properties.append(f"line={diagnostic.line}")
        message = _escape_workflow_command(f"[{diagnostic.code}] {diagnostic.message}")
        print(f"::{command} {','.join(properties)}::{message}")


def write_step_summary(report: ValidationReport, summary_path: Path) -> None:
    solution = report.solution or {}
    problem = report.problem or {}
    lines = [
        "## Solution format validation",
        "",
        f"- Result: **{'PASS' if report.valid else 'FAIL'}**",
        f"- File: `{solution.get('source_path', '-')}`",
        f"- Language: {solution.get('language', '-')}",
        f"- Author: {solution.get('author', '-')}",
        f"- Problem: {problem.get('title', '-')}",
        "",
    ]
    if report.errors or report.warnings:
        lines.extend(
            [
                "| Level | Code | Location | Message |",
                "| --- | --- | --- | --- |",
            ]
        )
        for diagnostic in [*report.errors, *report.warnings]:
            location = diagnostic.path
            if diagnostic.line is not None:
                location = f"{location}:{diagnostic.line}"
            message = diagnostic.message.replace("|", "\\|").replace("\n", " ")
            lines.append(
                f"| {diagnostic.severity} | {diagnostic.code} | `{location}` | {message} |"
            )
        lines.append("")
    else:
        lines.extend(["형식 오류가 없습니다.", ""])

    with summary_path.open("a", encoding="utf-8") as summary_file:
        summary_file.write("\n".join(lines))


def _comment_text(value: object) -> str:
    normalised = str(value).replace("\r", " ").replace("\n", " ")
    return html.escape(normalised, quote=False).replace("|", "&#124;")


def _comment_code(value: object) -> str:
    return f"<code>{_comment_text(value)}</code>"


def render_pr_comment(report: ValidationReport, run_url: str | None = None) -> str:
    solution = report.solution or {}
    problem = report.problem or {}
    status_icon = "✅" if report.valid else "❌"
    status_label = "통과" if report.valid else "실패"
    source_path = solution.get("source_path")
    if not source_path and len(report.changed_solution_files) == 1:
        source_path = report.changed_solution_files[0]

    lines = [
        COMMENT_MARKER,
        f"## {status_icon} 솔루션 형식 검사 {status_label}",
        "",
        "| 항목 | 결과 |",
        "| --- | --- |",
        f"| 파일 | {_comment_code(source_path or '-')} |",
        f"| 언어 | {_comment_text(solution.get('language', '-'))} |",
        f"| 작성자 | {_comment_text(solution.get('author', '-'))} |",
        f"| 문제 | {_comment_text(problem.get('title', '-'))} |",
        f"| 오류 | {len(report.errors)}개 |",
        f"| 경고 | {len(report.warnings)}개 |",
        "",
    ]

    diagnostics = [*report.errors, *report.warnings]
    if diagnostics:
        lines.extend(
            [
                "### 상세 결과",
                "",
                "| 수준 | 코드 | 위치 | 내용 |",
                "| --- | --- | --- | --- |",
            ]
        )
        for diagnostic in diagnostics[:30]:
            location = diagnostic.path
            if diagnostic.line is not None:
                location = f"{location}:{diagnostic.line}"
            level = "❌ 오류" if diagnostic.severity == "error" else "⚠️ 경고"
            lines.append(
                f"| {level} | {_comment_code(diagnostic.code)} | "
                f"{_comment_code(location)} | {_comment_text(diagnostic.message)} |"
            )
        if len(diagnostics) > 30:
            lines.extend(
                [
                    "",
                    (
                        f"> 나머지 {len(diagnostics) - 30}개 결과는 "
                        "Actions에서 확인하세요."
                    ),
                ]
            )
        lines.append("")
    else:
        lines.extend(["형식 오류와 경고가 없습니다.", ""])

    if run_url:
        parsed_url = urlsplit(run_url)
        if parsed_url.scheme in {"http", "https"} and parsed_url.netloc:
            lines.extend(
                [
                    f"[Actions 검사 실행 보기]({html.escape(run_url, quote=True)})",
                    "",
                ]
            )
    lines.append(
        "_새 커밋을 push하면 이 댓글을 최신 검사 결과로 갱신합니다._"
    )
    return "\n".join(lines) + "\n"


def _arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Validate a solution changed by a pull request")
    parser.add_argument("--repo-root", type=Path, default=Path.cwd())
    parser.add_argument("--base-sha", required=True)
    parser.add_argument("--head-sha", required=True)
    parser.add_argument("--config", type=Path)
    parser.add_argument("--result", type=Path, default=Path("validation-result.json"))
    parser.add_argument("--comment", type=Path)
    parser.add_argument("--pr-number", type=int)
    parser.add_argument("--run-url")
    return parser.parse_args()


def main() -> int:
    args = _arguments()
    repository_root = args.repo_root.resolve()
    try:
        changes = get_git_changes(repository_root, args.base_sha, args.head_sha)
    except subprocess.CalledProcessError as error:
        stderr = error.stderr.decode("utf-8", errors="replace") if error.stderr else str(error)
        print(f"git diff 실패: {stderr}", file=sys.stderr)
        return 2

    config_path = args.config
    if config_path is not None and not config_path.is_absolute():
        config_path = repository_root / config_path
    report = validate_changes(repository_root, changes, config_path)
    report.pr_number = args.pr_number

    result_path = args.result
    if not result_path.is_absolute():
        result_path = Path.cwd() / result_path
    result_path.write_text(
        json.dumps(report.as_dict(), ensure_ascii=False, indent=2) + "\n",
        encoding="utf-8",
    )
    if args.comment is not None:
        comment_path = args.comment
        if not comment_path.is_absolute():
            comment_path = Path.cwd() / comment_path
        comment_path.write_text(
            render_pr_comment(report, args.run_url),
            encoding="utf-8",
        )
    emit_annotations(report)

    summary_value = os.environ.get("GITHUB_STEP_SUMMARY")
    if summary_value:
        write_step_summary(report, Path(summary_value))
    else:
        for diagnostic in [*report.errors, *report.warnings]:
            print(diagnostic.format())

    return 0 if report.valid else 1


if __name__ == "__main__":
    raise SystemExit(main())

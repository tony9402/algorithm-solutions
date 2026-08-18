from __future__ import annotations

import argparse
import subprocess
import sys
import tempfile
from pathlib import Path


REPOSITORY_ROOT = Path(__file__).resolve().parents[1]
if str(REPOSITORY_ROOT) not in sys.path:
    sys.path.insert(0, str(REPOSITORY_ROOT))

from scripts.validate_solution_pr import (
    Change,
    get_merge_base,
    get_worktree_changes,
    validate_changes,
)
from scripts.solution_parser import parse_solution
from pages.problem_catalog import CatalogError, load_config


def _is_solution_change(change: Change) -> bool:
    paths = (change.path, change.old_path)
    return any(path and (path == "solutions" or path.startswith("solutions/")) for path in paths)


def _run_step(label: str, command: list[str], repository_root: Path) -> bool:
    print(f"\n== {label} ==", flush=True)
    completed = subprocess.run(command, cwd=repository_root)
    passed = completed.returncode == 0
    print(f"[{ 'PASS' if passed else 'FAIL' }] {label}", flush=True)
    return passed


def validate_local_solutions(repository_root: Path, changes: list[Change]) -> bool:
    print("\n== 전체 솔루션 검사 ==", flush=True)
    solution_paths = sorted((repository_root / "solutions").glob("*/*/*"))
    parse_results = [
        parse_solution(path, repository_root, mode="compat")
        for path in solution_paths
        if path.is_file() or path.is_symlink()
    ]
    baseline_errors = [
        diagnostic
        for result in parse_results
        for diagnostic in result.errors
    ]
    for diagnostic in baseline_errors:
        print(diagnostic.format())

    solution_changes = [change for change in changes if _is_solution_change(change)]
    if not solution_changes:
        if baseline_errors:
            print(f"[FAIL] 전체 솔루션: 오류 {len(baseline_errors)}개", flush=True)
            return False
        print(f"[PASS] 전체 솔루션 {len(parse_results)}개", flush=True)
        print("[SKIP] strict 검사가 필요한 변경 솔루션이 없습니다.", flush=True)
        return True

    config_path = repository_root / "pages" / "config.yaml"
    try:
        config_data = load_config(config_path)
    except (CatalogError, OSError, ValueError) as error:
        print(f"[FAIL] 문제 설정을 읽을 수 없습니다: {config_path}: {error}", flush=True)
        return False

    reports = [
        validate_changes(
            repository_root,
            [change],
            config_path=config_path,
            config_data=config_data,
        )
        for change in solution_changes
    ]
    for report in reports:
        for diagnostic in [*report.errors, *report.warnings]:
            print(diagnostic.format())

    valid = not baseline_errors and all(report.valid for report in reports)
    if valid:
        print(f"[PASS] 전체 솔루션 {len(parse_results)}개", flush=True)
        print(f"[PASS] 변경 솔루션 strict 형식 {len(reports)}개", flush=True)
    else:
        report_errors = sum(len(report.errors) for report in reports)
        report_warnings = sum(len(report.warnings) for report in reports)
        print(
            f"[FAIL] 솔루션 형식: 오류 {len(baseline_errors) + report_errors}개, "
            f"경고 {report_warnings}개",
            flush=True,
        )
    return valid


def _arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Run checks before opening a pull request")
    parser.add_argument(
        "--base-ref",
        default="origin/main",
        help="PR 대상 브랜치 또는 ref (기본값: origin/main)",
    )
    parser.add_argument("--repo-root", type=Path, default=REPOSITORY_ROOT)
    parser.add_argument(
        "--all",
        action="store_true",
        help="솔루션 형식 외에 전체 테스트와 Pages 빌드도 실행",
    )
    return parser.parse_args()


def main() -> int:
    args = _arguments()
    repository_root = args.repo_root.resolve()
    print(f"PR 사전 점검 기준: {args.base_ref}", flush=True)

    try:
        merge_base = get_merge_base(repository_root, args.base_ref)
        changes = get_worktree_changes(repository_root, merge_base)
    except (FileNotFoundError, subprocess.CalledProcessError) as error:
        detail = getattr(error, "stderr", b"")
        if isinstance(detail, bytes):
            detail = detail.decode("utf-8", errors="replace").strip()
        print(f"[FAIL] Git 변경 파일 확인 실패: {detail or error}", file=sys.stderr)
        return 2

    results = [("전체 솔루션", validate_local_solutions(repository_root, changes))]
    if args.all:
        results.append(
            (
                "전체 테스트",
                _run_step(
                    "전체 테스트",
                    [
                        sys.executable,
                        "-m",
                        "unittest",
                        "discover",
                        "-s",
                        "tests",
                        "-v",
                    ],
                    repository_root,
                ),
            )
        )
        with tempfile.TemporaryDirectory(prefix="algorithm-solutions-precheck-") as output:
            results.append(
                (
                    "GitHub Pages 빌드",
                    _run_step(
                        "GitHub Pages 빌드",
                        [sys.executable, "pages/build.py", "--output", output],
                        repository_root,
                    ),
                )
            )

    print("\n== 최종 결과 ==")
    for label, passed in results:
        print(f"[{ 'PASS' if passed else 'FAIL' }] {label}")
    if all(passed for _, passed in results):
        if args.all:
            print("PR을 올리기 전 자동 점검을 모두 통과했습니다.")
        else:
            print("전체 솔루션 검사를 통과했습니다.")
        return 0
    command = "make checkall" if args.all else "make precheck"
    print(f"실패한 항목을 수정한 뒤 {command}을 다시 실행하세요.")
    return 1


if __name__ == "__main__":
    raise SystemExit(main())

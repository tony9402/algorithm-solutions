from __future__ import annotations

import argparse
import json
import os
import re
import tempfile
from dataclasses import dataclass
from pathlib import Path
from urllib.error import HTTPError, URLError
from urllib.request import Request, urlopen

import yaml


REPOSITORY_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_CATALOG_URL = "https://leetcode.com/api/problems/all/"
SLUG_PATTERN = re.compile(r"^[a-z0-9]+(?:-[a-z0-9]+)*$")


class LeetCodeUpdateError(RuntimeError):
    pass


@dataclass(frozen=True)
class ProblemMetadata:
    problem_id: str
    title: str
    slug: str

    @property
    def url(self) -> str:
        return f"https://leetcode.com/problems/{self.slug}/"


@dataclass(frozen=True)
class UpdateResult:
    changed: bool
    problem_count: int


def fetch_catalog(url: str = DEFAULT_CATALOG_URL, timeout: float = 30.0) -> object:
    request = Request(
        url,
        headers={
            "Accept": "application/json",
            "User-Agent": "algorithm-solutions-leetcode-metadata-updater/1.0",
        },
    )
    try:
        with urlopen(request, timeout=timeout) as response:
            return json.load(response)
    except (HTTPError, URLError, TimeoutError, json.JSONDecodeError) as error:
        raise LeetCodeUpdateError(f"LeetCode 문제 목록을 가져오지 못했습니다: {error}") from error


def parse_catalog(payload: object) -> dict[str, ProblemMetadata]:
    if not isinstance(payload, dict):
        raise LeetCodeUpdateError("LeetCode 응답의 최상위 값이 JSON object가 아닙니다.")
    rows = payload.get("stat_status_pairs")
    if not isinstance(rows, list):
        raise LeetCodeUpdateError("LeetCode 응답에 stat_status_pairs 목록이 없습니다.")

    catalog: dict[str, ProblemMetadata] = {}
    for row in rows:
        if not isinstance(row, dict) or not isinstance(row.get("stat"), dict):
            continue
        if row.get("paid_only") is True:
            continue
        stat = row["stat"]
        problem_id = str(stat.get("frontend_question_id", "")).strip()
        title = str(stat.get("question__title", "")).strip()
        slug = str(stat.get("question__title_slug", "")).strip().lower()
        if not problem_id.isdigit():
            continue
        if not title or not SLUG_PATTERN.fullmatch(slug):
            continue

        metadata = ProblemMetadata(problem_id=problem_id, title=title, slug=slug)
        previous = catalog.get(problem_id)
        if previous is not None and previous != metadata:
            raise LeetCodeUpdateError(f"LeetCode 문제 번호가 중복됩니다: {problem_id}")
        catalog[problem_id] = metadata

    if not catalog:
        raise LeetCodeUpdateError("LeetCode 응답에서 유효한 문제 정보를 찾지 못했습니다.")
    return catalog


def _load_config(path: Path) -> dict:
    try:
        config = yaml.safe_load(path.read_text(encoding="utf-8"))
    except (OSError, yaml.YAMLError) as error:
        raise LeetCodeUpdateError(f"설정 파일을 읽지 못했습니다: {path}: {error}") from error
    if not isinstance(config, dict):
        raise LeetCodeUpdateError(f"설정 파일의 최상위 값은 mapping이어야 합니다: {path}")
    return config


def _render_config(config: dict) -> str:
    return yaml.safe_dump(
        config,
        allow_unicode=True,
        sort_keys=False,
        default_flow_style=False,
        width=1000,
    )


def _atomic_write(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    descriptor, temporary_name = tempfile.mkstemp(
        prefix=f".{path.name}.",
        suffix=".tmp",
        dir=path.parent,
        text=True,
    )
    temporary_path = Path(temporary_name)
    try:
        with os.fdopen(descriptor, "w", encoding="utf-8") as output:
            output.write(content)
        os.replace(temporary_path, path)
    except BaseException:
        temporary_path.unlink(missing_ok=True)
        raise


def update_config(
    config_path: Path,
    catalog: dict[str, ProblemMetadata],
    *,
    check: bool = False,
) -> UpdateResult:
    config = _load_config(config_path)
    current_problems = config.get("problems", {})
    if not isinstance(current_problems, dict):
        raise LeetCodeUpdateError("config.yaml의 problems 값은 mapping이어야 합니다.")

    problems: dict[str, object] = {}
    for problem_id, metadata in sorted(catalog.items(), key=lambda item: int(item[0])):
        problems[f"leetcode/{problem_id}"] = {
            "title": metadata.title,
            "url": metadata.url,
        }
    for key, value in current_problems.items():
        if not str(key).startswith("leetcode/"):
            problems[str(key)] = value
    config["problems"] = problems

    rendered = _render_config(config)
    current = config_path.read_text(encoding="utf-8")
    changed = rendered != current
    if changed and not check:
        _atomic_write(config_path, rendered)
    return UpdateResult(changed=changed, problem_count=len(catalog))


def _arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "LeetCode 전체 문제 카탈로그를 가져와 프리미엄 문제를 제외한 모든 문제의 "
            "제목과 URL을 pages/config.yaml에 기록합니다."
        )
    )
    parser.add_argument("--repository-root", type=Path, default=REPOSITORY_ROOT)
    parser.add_argument("--config", type=Path, default=Path("pages/config.yaml"))
    parser.add_argument("--catalog-url", default=DEFAULT_CATALOG_URL)
    parser.add_argument("--catalog-file", type=Path, help="네트워크 대신 사용할 LeetCode JSON 파일")
    parser.add_argument("--timeout", type=float, default=30.0)
    parser.add_argument("--check", action="store_true", help="파일을 수정하지 않고 최신 상태인지 확인")
    return parser.parse_args()


def main() -> int:
    args = _arguments()
    repository_root = args.repository_root.resolve()
    config_path = args.config
    if not config_path.is_absolute():
        config_path = repository_root / config_path

    try:
        if args.catalog_file:
            payload = json.loads(args.catalog_file.read_text(encoding="utf-8"))
        else:
            payload = fetch_catalog(args.catalog_url, args.timeout)
        catalog = parse_catalog(payload)
        result = update_config(
            config_path,
            catalog,
            check=args.check,
        )
    except (OSError, json.JSONDecodeError, LeetCodeUpdateError) as error:
        print(f"[FAIL] {error}")
        return 1

    if args.check and result.changed:
        print(
            f"[FAIL] {config_path}의 LeetCode 문제 정보가 최신 상태가 아닙니다. "
            "업데이트 명령을 실행하세요."
        )
        return 1
    if result.changed:
        print(f"[PASS] LeetCode 무료 문제 {result.problem_count}개의 제목과 URL을 갱신했습니다.")
    else:
        print(f"[PASS] LeetCode 무료 문제 {result.problem_count}개의 제목과 URL이 이미 최신입니다.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

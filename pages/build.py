from __future__ import annotations

import argparse
import json
import os
import re
import shutil
import sys
from collections import Counter, defaultdict
from dataclasses import dataclass
from datetime import datetime
from pathlib import Path
from urllib.parse import quote
from zoneinfo import ZoneInfo, ZoneInfoNotFoundError

from jinja2 import Environment, FileSystemLoader, select_autoescape
from pygments import highlight
from pygments.formatters import HtmlFormatter
from pygments.lexers import get_lexer_by_name


REPOSITORY_ROOT = Path(__file__).resolve().parents[1]
if str(REPOSITORY_ROOT) not in sys.path:
    sys.path.insert(0, str(REPOSITORY_ROOT))

from pages.announcements import AnnouncementError, load_announcements
from pages.problem_catalog import CatalogError, ProblemInfo, load_config, resolve_problem
from scripts.solution_parser import Diagnostic, ParsedSolution, parse_solution


class SiteBuildError(RuntimeError):
    pass


HIGHLIGHT_STYLE = "monokai"
COMMUNITY_TIER_GROUPS = ("Bronze", "Silver", "Gold", "Platinum", "Diamond", "Ruby")
COMMUNITY_TIER_RANKS = ("V", "IV", "III", "II", "I")


@dataclass
class RenderedSolution:
    platform: str
    problem_id: str
    filename: str
    language: str
    source_path: str
    author: str
    coauthors: list[str]
    submission_url: str | None
    solution_description: str | None
    highlighted_code: str
    anchor: str
    github_url: str


@dataclass
class ProblemPage:
    platform: str
    platform_label: str
    problem_id: str
    title: str
    external_url: str
    internal_path: str
    solutions: list[RenderedSolution]
    languages: list[str]
    search_text: str

    @property
    def solution_count(self) -> int:
        return len(self.solutions)

    @property
    def key(self) -> str:
        return f"{self.platform}/{self.problem_id}"


@dataclass(frozen=True)
class BuildResult:
    solution_count: int
    problem_count: int
    warning_count: int
    output_path: Path


def normalise_base_path(value: str) -> str:
    value = value.strip()
    if not value or value == "/":
        return ""
    if "://" in value or "?" in value or "#" in value:
        raise SiteBuildError(f"base path는 URL이 아닌 경로여야 합니다: {value}")
    parts = [part for part in value.split("/") if part]
    if any(part in {".", ".."} for part in parts):
        raise SiteBuildError(f"base path에 상대 경로를 사용할 수 없습니다: {value}")
    return "/" + "/".join(parts)


def _anchor(filename: str) -> str:
    slug = re.sub(r"[^a-zA-Z0-9]+", "-", filename).strip("-").lower()
    return f"solution-{slug or 'source'}"


def _problem_sort_key(problem: ProblemPage, platform_order: dict[str, int]) -> tuple[int, int, str]:
    return (
        platform_order.get(problem.platform, len(platform_order)),
        int(problem.problem_id),
        problem.problem_id,
    )


def _render_solution(solution: ParsedSolution, repository_url: str) -> RenderedSolution:
    formatter = HtmlFormatter(nowrap=True, style=HIGHLIGHT_STYLE)
    lexer = get_lexer_by_name(solution.lexer, stripall=False)
    highlighted = highlight(solution.code, lexer, formatter)
    github_url = f"{repository_url.rstrip('/')}/blob/main/{quote(solution.source_path)}"
    return RenderedSolution(
        platform=solution.platform,
        problem_id=solution.problem_id,
        filename=solution.filename,
        language=solution.language,
        source_path=solution.source_path,
        author=solution.author,
        coauthors=solution.coauthors,
        submission_url=solution.submission_url,
        solution_description=solution.solution_description,
        highlighted_code=highlighted,
        anchor=_anchor(solution.filename),
        github_url=github_url,
    )


def _collect_solutions(repository_root: Path) -> tuple[list[ParsedSolution], list[Diagnostic]]:
    solutions: list[ParsedSolution] = []
    diagnostics: list[Diagnostic] = []
    for path in sorted((repository_root / "solutions").glob("*/*/*")):
        if not path.is_file() and not path.is_symlink():
            continue
        result = parse_solution(path, repository_root, mode="compat")
        diagnostics.extend(result.diagnostics)
        if result.solution is not None:
            solutions.append(result.solution)
    return solutions, diagnostics


def _build_problem_pages(config: dict, solutions: list[ParsedSolution]) -> list[ProblemPage]:
    grouped: dict[tuple[str, str], list[ParsedSolution]] = defaultdict(list)
    for solution in solutions:
        grouped[(solution.platform, solution.problem_id)].append(solution)

    repository_url = str(config.get("site", {}).get("repository_url", "")).strip()
    if not repository_url.startswith(("https://", "http://")):
        raise SiteBuildError(
            "site.repository_url은 절대 http 또는 https URL이어야 합니다."
        )

    pages: list[ProblemPage] = []
    for (platform, problem_id), problem_solutions in grouped.items():
        problem_info: ProblemInfo = resolve_problem(
            config,
            platform,
            problem_id,
            [solution.submission_url for solution in problem_solutions],
        )
        rendered = sorted(
            (_render_solution(solution, repository_url) for solution in problem_solutions),
            key=lambda solution: (solution.language.casefold(), solution.filename.casefold()),
        )
        languages = sorted({solution.language for solution in rendered}, key=str.casefold)
        search_text = " ".join(
            [
                problem_info.title,
                problem_info.platform_label,
                problem_id,
                *languages,
            ]
        ).casefold()
        pages.append(
            ProblemPage(
                platform=platform,
                platform_label=problem_info.platform_label,
                problem_id=problem_id,
                title=problem_info.title,
                external_url=problem_info.url,
                internal_path=f"problems/{platform}/{problem_id}/",
                solutions=rendered,
                languages=languages,
                search_text=search_text,
            )
        )

    platform_order = {
        platform: index for index, platform in enumerate(config.get("platforms", {}).keys())
    }
    return sorted(pages, key=lambda problem: _problem_sort_key(problem, platform_order))


def _validate_counts(
    config: dict,
    solutions: list[ParsedSolution],
    problems: list[ProblemPage],
) -> None:
    validation = config.get("validation", {})
    minimum_solutions = int(validation.get("minimum_solution_count", 0))
    minimum_problems = int(validation.get("minimum_problem_count", 0))
    if len(solutions) < minimum_solutions:
        raise SiteBuildError(
            f"솔루션 수가 기준선보다 적습니다: {len(solutions)} < {minimum_solutions}"
        )
    if len(problems) < minimum_problems:
        raise SiteBuildError(
            f"문제 수가 기준선보다 적습니다: {len(problems)} < {minimum_problems}"
        )


def _make_environment(template_directory: Path, base_path: str) -> Environment:
    environment = Environment(
        loader=FileSystemLoader(template_directory),
        autoescape=select_autoescape(("html", "xml")),
        trim_blocks=True,
        lstrip_blocks=True,
    )

    def url_for(path: str = "") -> str:
        normalised = path.lstrip("/")
        suffix = f"/{normalised}" if normalised else "/"
        return f"{base_path}{suffix}"

    environment.globals["url_for"] = url_for
    return environment


def _write_json(path: Path, data: object) -> None:
    path.write_text(json.dumps(data, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def _load_community_snapshot(path: Path, repository_url: str) -> dict:
    default = {
        "schema_version": 1,
        "repository": repository_url.rstrip("/").removeprefix("https://github.com/"),
        "configuration": {
            "comments_category": None,
            "ratings_category": None,
            "ready": False,
        },
        "summary": {"problem_count": 0, "rating_count": 0, "comment_count": 0},
        "problems": {},
        "generated_at": None,
    }
    if not path.is_file():
        return default
    try:
        snapshot = json.loads(path.read_text(encoding="utf-8"))
    except json.JSONDecodeError as error:
        raise SiteBuildError(f"커뮤니티 데이터 JSON이 올바르지 않습니다: {path}: {error}") from error
    if not isinstance(snapshot, dict) or snapshot.get("schema_version") != 1:
        raise SiteBuildError(f"지원하지 않는 커뮤니티 데이터 형식입니다: {path}")
    if not isinstance(snapshot.get("configuration"), dict):
        raise SiteBuildError(f"커뮤니티 데이터 configuration이 올바르지 않습니다: {path}")
    if not isinstance(snapshot.get("problems"), dict):
        raise SiteBuildError(f"커뮤니티 데이터 problems가 올바르지 않습니다: {path}")
    return snapshot


def _community_tier_options() -> list[dict[str, object]]:
    options: list[dict[str, object]] = []
    value = 1
    for group in COMMUNITY_TIER_GROUPS:
        tiers = []
        for rank in COMMUNITY_TIER_RANKS:
            tiers.append({"value": value, "name": f"{group} {rank}"})
            value += 1
        options.append({"group": group, "tiers": tiers})
    return options


def build_site(
    repository_root: Path,
    config_path: Path,
    output_path: Path,
    base_path: str | None = None,
) -> BuildResult:
    repository_root = repository_root.resolve()
    config_path = config_path if config_path.is_absolute() else repository_root / config_path
    output_path = output_path if output_path.is_absolute() else repository_root / output_path
    config = load_config(config_path)
    if base_path is None:
        base_path = str(config.get("site", {}).get("default_base_path", ""))
    base_path = normalise_base_path(base_path)
    solutions, diagnostics = _collect_solutions(repository_root)
    errors = [item for item in diagnostics if item.severity == "error"]
    warnings = [item for item in diagnostics if item.severity == "warning"]
    if errors:
        formatted = "\n".join(item.format() for item in errors[:50])
        raise SiteBuildError(f"솔루션 파싱 오류 {len(errors)}개:\n{formatted}")

    try:
        problems = _build_problem_pages(config, solutions)
    except CatalogError as error:
        raise SiteBuildError(str(error)) from error
    _validate_counts(config, solutions, problems)

    pages_directory = repository_root / "pages"
    environment = _make_environment(pages_directory / "templates", base_path)
    site_config = config.get("site", {})
    repository_url = str(site_config.get("repository_url", "")).strip()
    community_settings = config.get("community", {})
    if not isinstance(community_settings, dict):
        raise SiteBuildError("community 설정은 mapping이어야 합니다.")
    community_vote_api_url = (
        os.environ.get("COMMUNITY_VOTE_API_URL")
        or str(community_settings.get("vote_api_url", ""))
    ).strip().rstrip("/")
    if community_vote_api_url and not community_vote_api_url.startswith(("https://", "http://")):
        raise SiteBuildError("community.vote_api_url은 절대 HTTP(S) URL이어야 합니다.")
    community_snapshot = _load_community_snapshot(
        repository_root / "community-data" / "discussions.json",
        repository_url,
    )
    community_config = community_snapshot["configuration"]
    community_problems = community_snapshot["problems"]
    announcement_config = config.get("announcements", {})
    try:
        timezone = ZoneInfo(str(announcement_config.get("timezone", "Asia/Seoul")))
    except (ZoneInfoNotFoundError, ValueError) as error:
        raise SiteBuildError(
            "announcements.timezone이 올바른 IANA 시간대가 아닙니다."
        ) from error
    announcement_directory_setting = Path(
        str(announcement_config.get("directory", "announcements"))
    )
    if (
        announcement_directory_setting.is_absolute()
        or ".." in announcement_directory_setting.parts
    ):
        raise SiteBuildError(
            "announcements.directory는 저장소 내부의 상대 경로여야 합니다."
        )
    try:
        announcements = load_announcements(
            repository_root / announcement_directory_setting,
            today=datetime.now(timezone).date(),
            recent_days=int(announcement_config.get("recent_days", 7)),
        )
    except (AnnouncementError, ValueError) as error:
        raise SiteBuildError(str(error)) from error
    recent_announcement_ids = [
        announcement.announcement_id for announcement in announcements if announcement.is_recent
    ]
    context = {
        "site": site_config,
        "base_path": base_path,
        "problem_count": len(problems),
        "solution_count": len(solutions),
        "recent_announcement_ids": recent_announcement_ids,
        "community_config": community_config,
        "community_repository": community_snapshot.get("repository", ""),
        "community_generated_at": community_snapshot.get("generated_at"),
        "community_vote_api_url": community_vote_api_url,
        "community_tier_options": _community_tier_options(),
    }

    if output_path.exists():
        shutil.rmtree(output_path)
    output_path.mkdir(parents=True)

    static_output = output_path / "assets"
    shutil.copytree(pages_directory / "assets", static_output)
    formatter = HtmlFormatter(style=HIGHLIGHT_STYLE)
    (static_output / "highlight.css").write_text(
        formatter.get_style_defs(".highlight") + "\n",
        encoding="utf-8",
    )

    index_template = environment.get_template("index.html")
    platform_options = [
        {
            "value": platform,
            "label": platform_config.get("label", platform),
        }
        for platform, platform_config in config.get("platforms", {}).items()
    ]
    language_options = sorted(
        {language for problem in problems for language in problem.languages}, key=str.casefold
    )
    page_size = int(site_config.get("catalog_page_size", 30))
    if page_size < 1:
        raise SiteBuildError("site.catalog_page_size는 1 이상이어야 합니다.")
    (output_path / "index.html").write_text(
        index_template.render(
            **context,
            page_title=str(site_config.get("title", "Algorithm Solutions")),
            active_nav="solutions",
            problems=problems,
            platform_options=platform_options,
            language_options=language_options,
            page_size=page_size,
        ),
        encoding="utf-8",
    )

    announcement_template = environment.get_template("announcements.html")
    announcement_directory = output_path / "announcements"
    announcement_directory.mkdir(parents=True)
    (announcement_directory / "index.html").write_text(
        announcement_template.render(
            **context,
            page_title=f"공지사항 · {site_config.get('title', 'Algorithm Solutions')}",
            active_nav="announcements",
            announcements=announcements,
        ),
        encoding="utf-8",
    )

    problem_template = environment.get_template("problem.html")
    for problem in problems:
        directory = output_path / "problems" / problem.platform / problem.problem_id
        directory.mkdir(parents=True)
        (directory / "index.html").write_text(
            problem_template.render(
                **context,
                page_title=f"{problem.title} · {site_config.get('title', 'Algorithm Solutions')}",
                active_nav="solutions",
                problem=problem,
                community=community_problems.get(problem.key, {}),
            ),
            encoding="utf-8",
        )

    not_found_template = environment.get_template("404.html")
    (output_path / "404.html").write_text(
        not_found_template.render(
            **context,
            page_title=(
                f"페이지를 찾을 수 없음 · "
                f"{site_config.get('title', 'Algorithm Solutions')}"
            ),
            active_nav="",
        ),
        encoding="utf-8",
    )
    (output_path / ".nojekyll").write_text("", encoding="utf-8")

    search_index = [
        {
            "platform": problem.platform,
            "platform_label": problem.platform_label,
            "problem_id": problem.problem_id,
            "title": problem.title,
            "url": f"{base_path}/{problem.internal_path}",
            "external_url": problem.external_url,
            "languages": problem.languages,
            "solution_count": problem.solution_count,
        }
        for problem in problems
    ]
    _write_json(static_output / "search-index.json", search_index)
    _write_json(static_output / "community-data.json", community_snapshot)

    warning_counts = Counter(item.code for item in warnings)
    if warnings:
        summary = ", ".join(f"{code}={count}" for code, count in sorted(warning_counts.items()))
        print(f"호환 파서 경고 {len(warnings)}개 ({summary})", file=sys.stderr)

    print(f"Generated {len(problems)} problem pages from {len(solutions)} solutions: {output_path}")
    return BuildResult(len(solutions), len(problems), len(warnings), output_path)


def _arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Build the Algorithm Solutions static site")
    parser.add_argument("--repo-root", type=Path, default=REPOSITORY_ROOT)
    parser.add_argument("--config", type=Path, default=Path("pages/config.yaml"))
    parser.add_argument("--output", type=Path, default=Path("_site"))
    parser.add_argument("--base-path")
    return parser.parse_args()


def main() -> int:
    args = _arguments()
    try:
        build_site(args.repo_root, args.config, args.output, args.base_path)
    except (SiteBuildError, CatalogError, OSError, ValueError) as error:
        print(f"Pages build failed: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

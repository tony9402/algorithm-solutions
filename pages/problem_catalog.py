from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from urllib.parse import urlparse

import yaml


@dataclass(frozen=True)
class ProblemInfo:
    platform: str
    platform_label: str
    problem_id: str
    title: str
    url: str


class CatalogError(ValueError):
    pass


def load_config(path: Path) -> dict:
    with path.open("r", encoding="utf-8") as config_file:
        config = yaml.safe_load(config_file)
    if not isinstance(config, dict):
        raise CatalogError(f"설정 파일의 최상위 값은 mapping이어야 합니다: {path}")
    return config


def _valid_http_url(value: str) -> bool:
    parsed = urlparse(value)
    return parsed.scheme in {"http", "https"} and bool(parsed.netloc)


def _leetcode_problem_url(submission_url: str | None) -> str | None:
    if not submission_url:
        return None
    parsed = urlparse(submission_url)
    if parsed.netloc.lower() not in {"leetcode.com", "www.leetcode.com"}:
        return None
    parts = [part for part in parsed.path.split("/") if part]
    if len(parts) < 2 or parts[0] != "problems":
        return None
    slug = parts[1]
    if not slug or any(character not in "abcdefghijklmnopqrstuvwxyz0123456789-" for character in slug.lower()):
        return None
    return f"https://leetcode.com/problems/{slug}/"


def resolve_problem(
    config: dict,
    platform: str,
    problem_id: str,
    submission_urls: list[str | None] | None = None,
) -> ProblemInfo:
    platforms = config.get("platforms", {})
    platform_config = platforms.get(platform)
    if not isinstance(platform_config, dict):
        raise CatalogError(f"config.yaml에 플랫폼 설정이 없습니다: {platform}")

    label = str(platform_config.get("label", platform))
    problem_key = f"{platform}/{problem_id}"
    overrides = config.get("problems", {})
    override = overrides.get(problem_key, {}) if isinstance(overrides, dict) else {}
    if override and not isinstance(override, dict):
        raise CatalogError(f"문제 override는 mapping이어야 합니다: {problem_key}")

    problem_url = str(override.get("url", "")).strip()
    if not problem_url and platform == "leetcode":
        for submission_url in submission_urls or []:
            problem_url = _leetcode_problem_url(submission_url) or ""
            if problem_url:
                break

    template = str(platform_config.get("problem_url_template", "")).strip()
    if not problem_url and template:
        try:
            problem_url = template.format(problem_id=problem_id)
        except KeyError as error:
            raise CatalogError(f"문제 URL template 변수가 잘못되었습니다: {platform}: {error}") from error

    if not problem_url:
        raise CatalogError(f"외부 문제 URL을 결정할 수 없습니다: {problem_key}")
    if not _valid_http_url(problem_url):
        raise CatalogError(f"외부 문제 URL이 올바르지 않습니다: {problem_key}: {problem_url}")

    title = str(override.get("title", "")).strip() or f"{label} #{problem_id}"
    return ProblemInfo(
        platform=platform,
        platform_label=label,
        problem_id=problem_id,
        title=title,
        url=problem_url,
    )

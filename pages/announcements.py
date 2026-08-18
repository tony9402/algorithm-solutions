from __future__ import annotations

import html
import re
from dataclasses import dataclass
from datetime import date
from html.parser import HTMLParser
from pathlib import Path
from urllib.parse import urlsplit

import markdown
import yaml


class AnnouncementError(ValueError):
    pass


@dataclass(frozen=True)
class Announcement:
    announcement_id: str
    title: str
    published_at: date
    published_label: str
    body_html: str
    is_recent: bool


_FRONT_MATTER = re.compile(
    r"\A---\r?\n(?P<metadata>.*?)\r?\n---(?:\r?\n)?(?P<body>.*)\Z",
    re.DOTALL,
)
_ANNOUNCEMENT_ID = re.compile(r"[a-z0-9](?:[a-z0-9-]*[a-z0-9])?")
_LANGUAGE_CLASS = re.compile(r"language-[a-zA-Z0-9_+-]+")
_ALLOWED_TAGS = {
    "a",
    "blockquote",
    "br",
    "code",
    "em",
    "h1",
    "h2",
    "h3",
    "h4",
    "hr",
    "li",
    "ol",
    "p",
    "pre",
    "strong",
    "ul",
}
_VOID_TAGS = {"br", "hr"}


def _safe_href(value: str) -> str | None:
    value = value.strip()
    if value.startswith("#"):
        return value
    parsed = urlsplit(value)
    if parsed.scheme in {"http", "https", "mailto"}:
        return value
    return None


class _SafeAnnouncementHtml(HTMLParser):
    def __init__(self) -> None:
        super().__init__(convert_charrefs=False)
        self.output: list[str] = []

    def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
        tag = tag.lower()
        if tag not in _ALLOWED_TAGS:
            return

        safe_attrs: list[tuple[str, str]] = []
        attributes = dict(attrs)
        if tag == "a":
            href = _safe_href(attributes.get("href") or "")
            if href:
                safe_attrs.append(("href", href))
                if urlsplit(href).scheme in {"http", "https"}:
                    safe_attrs.extend(
                        [("target", "_blank"), ("rel", "noopener noreferrer")]
                    )
            if attributes.get("title"):
                safe_attrs.append(("title", attributes["title"] or ""))
        elif tag == "code":
            class_name = attributes.get("class") or ""
            if _LANGUAGE_CLASS.fullmatch(class_name):
                safe_attrs.append(("class", class_name))

        rendered_attrs = "".join(
            f' {name}="{html.escape(value, quote=True)}"' for name, value in safe_attrs
        )
        self.output.append(f"<{tag}{rendered_attrs}>")

    def handle_endtag(self, tag: str) -> None:
        tag = tag.lower()
        if tag in _ALLOWED_TAGS and tag not in _VOID_TAGS:
            self.output.append(f"</{tag}>")

    def handle_startendtag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
        self.handle_starttag(tag, attrs)

    def handle_data(self, data: str) -> None:
        self.output.append(data)

    def handle_entityref(self, name: str) -> None:
        self.output.append(f"&{name};")

    def handle_charref(self, name: str) -> None:
        self.output.append(f"&#{name};")


def render_announcement_markdown(source: str) -> str:
    escaped_source = html.escape(source, quote=False)
    rendered = markdown.markdown(
        escaped_source,
        extensions=["fenced_code", "sane_lists"],
        output_format="html",
    )
    sanitizer = _SafeAnnouncementHtml()
    sanitizer.feed(rendered)
    sanitizer.close()
    return "".join(sanitizer.output)


def _parse_date(value: object, path: Path) -> date:
    if isinstance(value, date):
        return value
    if isinstance(value, str):
        try:
            return date.fromisoformat(value)
        except ValueError as error:
            raise AnnouncementError(
                f"{path}: date는 YYYY-MM-DD 형식이어야 합니다."
            ) from error
    raise AnnouncementError(f"{path}: date는 YYYY-MM-DD 형식이어야 합니다.")


def load_announcements(
    directory: Path,
    *,
    today: date,
    recent_days: int = 7,
) -> list[Announcement]:
    if recent_days < 1:
        raise AnnouncementError("announcements.recent_days는 1 이상이어야 합니다.")
    if not directory.exists():
        return []
    if not directory.is_dir():
        raise AnnouncementError(f"공지 경로가 디렉터리가 아닙니다: {directory}")

    announcements: list[Announcement] = []
    for path in sorted(directory.glob("*.md")):
        if path.name.casefold() == "readme.md":
            continue
        if path.is_symlink() or not path.is_file():
            raise AnnouncementError(f"공지 파일은 일반 파일이어야 합니다: {path}")
        if not _ANNOUNCEMENT_ID.fullmatch(path.stem):
            raise AnnouncementError(
                f"{path}: 파일명은 영문 소문자, 숫자, "
                "하이픈만 사용할 수 있습니다."
            )

        try:
            source = path.read_text(encoding="utf-8")
        except UnicodeError as error:
            raise AnnouncementError(f"{path}: UTF-8 파일이 아닙니다.") from error
        match = _FRONT_MATTER.fullmatch(source)
        if not match:
            raise AnnouncementError(
                f"{path}: YAML front matter가 없거나 닫히지 않았습니다."
            )

        try:
            metadata = yaml.safe_load(match.group("metadata")) or {}
        except yaml.YAMLError as error:
            raise AnnouncementError(
                f"{path}: YAML front matter를 읽을 수 없습니다."
            ) from error
        if not isinstance(metadata, dict):
            raise AnnouncementError(
                f"{path}: YAML front matter는 key-value 형식이어야 합니다."
            )

        title = metadata.get("title")
        if not isinstance(title, str) or not title.strip():
            raise AnnouncementError(f"{path}: 비어 있지 않은 title이 필요합니다.")
        published_at = _parse_date(metadata.get("date"), path)
        if published_at > today:
            raise AnnouncementError(
                f"{path}: 미래 날짜의 공지는 게시할 수 없습니다."
            )
        body = match.group("body").strip()
        if not body:
            raise AnnouncementError(f"{path}: 공지 본문이 비어 있습니다.")

        age_in_days = (today - published_at).days
        announcements.append(
            Announcement(
                announcement_id=path.stem,
                title=title.strip(),
                published_at=published_at,
                published_label=published_at.strftime("%Y. %m. %d."),
                body_html=render_announcement_markdown(body),
                is_recent=age_in_days < recent_days,
            )
        )

    return sorted(
        announcements,
        key=lambda announcement: (announcement.published_at, announcement.announcement_id),
        reverse=True,
    )

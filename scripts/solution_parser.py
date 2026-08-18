from __future__ import annotations

import re
from dataclasses import asdict, dataclass, field
from pathlib import Path
from typing import Iterable, Literal
from urllib.parse import urlparse


Severity = Literal["error", "warning"]
ParseMode = Literal["compat", "strict"]

ALLOWED_PLATFORMS = ("baekjoon", "leetcode", "programmers", "hackerrank")
METADATA_KEYS = ("Authored by", "Co-authored by", "Link")
HEADER_SCAN_LIMIT = 10


@dataclass(frozen=True)
class LanguageSpec:
    extension: str
    language: str
    lexer: str
    line_comment: str
    description_kind: Literal["block", "python"]
    filename_pattern: re.Pattern[str]


def _filename_pattern(stem: str, extension: str) -> re.Pattern[str]:
    return re.compile(rf"{stem}(?:[2-9][0-9]*)?\.{re.escape(extension)}")


LANGUAGE_SPECS: dict[str, LanguageSpec] = {
    "c": LanguageSpec("c", "C", "c", "//", "block", _filename_pattern("main", "c")),
    "cpp": LanguageSpec("cpp", "C++", "cpp", "//", "block", _filename_pattern("main", "cpp")),
    "py": LanguageSpec("py", "Python", "python", "#", "python", _filename_pattern("main", "py")),
    "java": LanguageSpec("java", "Java", "java", "//", "block", _filename_pattern("Main", "java")),
    "kt": LanguageSpec("kt", "Kotlin", "kotlin", "//", "block", _filename_pattern("main", "kt")),
    "js": LanguageSpec("js", "JavaScript", "javascript", "//", "block", _filename_pattern("main", "js")),
    "rs": LanguageSpec("rs", "Rust", "rust", "//", "block", _filename_pattern("main", "rs")),
    "swift": LanguageSpec("swift", "Swift", "swift", "//", "block", _filename_pattern("main", "swift")),
    "go": LanguageSpec("go", "Go", "go", "//", "block", _filename_pattern("main", "go")),
    "sql": LanguageSpec("sql", "SQL", "sql", "--", "block", _filename_pattern("main", "sql")),
}

EXTENSION_TO_LANGUAGE = {extension: spec.language for extension, spec in LANGUAGE_SPECS.items()}
EXTENSION_TO_LEXER = {extension: spec.lexer for extension, spec in LANGUAGE_SPECS.items()}


@dataclass(frozen=True)
class Diagnostic:
    code: str
    severity: Severity
    message: str
    path: str
    line: int | None = None

    def as_dict(self) -> dict[str, object]:
        return asdict(self)

    def format(self) -> str:
        location = self.path
        if self.line is not None:
            location = f"{location}:{self.line}"
        return f"{self.code} {location} {self.message}"


@dataclass
class ParsedSolution:
    platform: str
    problem_id: str
    filename: str
    extension: str
    language: str
    lexer: str
    source_path: str
    author: str
    coauthors: list[str]
    submission_url: str | None
    code: str
    solution_description: str | None

    def as_dict(self) -> dict[str, object]:
        return asdict(self)


@dataclass
class ParseResult:
    solution: ParsedSolution | None = None
    diagnostics: list[Diagnostic] = field(default_factory=list)

    @property
    def errors(self) -> list[Diagnostic]:
        return [item for item in self.diagnostics if item.severity == "error"]

    @property
    def warnings(self) -> list[Diagnostic]:
        return [item for item in self.diagnostics if item.severity == "warning"]

    @property
    def valid(self) -> bool:
        return not self.errors


@dataclass(frozen=True)
class _MetadataMatch:
    key: str
    value: str
    prefix: str
    canonical: bool


_LEGACY_METADATA_PATTERN = re.compile(
    r"^\s*(?P<prefix>//|#|--)\s*"
    r"(?:(?://|#|--)\s*)?"
    r"(?P<key>Authored by|Co-authored by|Link)\s*:\s*(?P<value>.*?)\s*$",
    re.IGNORECASE,
)


def _canonical_metadata_pattern(spec: LanguageSpec) -> re.Pattern[str]:
    return re.compile(
        rf"^{re.escape(spec.line_comment)} "
        r"(?P<key>Authored by|Co-authored by|Link):(?: (?P<value>.*))?$"
    )


def _normalise_key(key: str) -> str:
    lowered = key.lower()
    return next(candidate for candidate in METADATA_KEYS if candidate.lower() == lowered)


def _match_metadata(line: str, spec: LanguageSpec | None = None) -> _MetadataMatch | None:
    content = line.rstrip("\r\n")
    if spec is not None:
        canonical_match = _canonical_metadata_pattern(spec).fullmatch(content)
        if canonical_match:
            return _MetadataMatch(
                key=_normalise_key(canonical_match.group("key")),
                value=(canonical_match.group("value") or "").strip(),
                prefix=spec.line_comment,
                canonical=True,
            )

    legacy_match = _LEGACY_METADATA_PATTERN.fullmatch(content)
    if not legacy_match:
        return None

    return _MetadataMatch(
        key=_normalise_key(legacy_match.group("key")),
        value=legacy_match.group("value").strip(),
        prefix=legacy_match.group("prefix"),
        canonical=False,
    )


def parse_metadata_lines(lines: Iterable[str]) -> dict[str, str]:
    """Return legacy-compatible metadata for existing upload scripts."""

    metadata: dict[str, str] = {}
    for line in list(lines)[:HEADER_SCAN_LIMIT]:
        match = _match_metadata(line)
        if match is not None and match.key not in metadata:
            metadata[match.key] = match.value
    return metadata


def _is_http_url(value: str) -> bool:
    parsed = urlparse(value)
    return parsed.scheme in {"http", "https"} and bool(parsed.netloc)


def _trim_blank_edges(lines: list[str]) -> list[str]:
    start = 0
    end = len(lines)
    while start < end and not lines[start].strip():
        start += 1
    while end > start and not lines[end - 1].strip():
        end -= 1
    return lines[start:end]


def _diagnostic(
    diagnostics: list[Diagnostic],
    code: str,
    severity: Severity,
    message: str,
    path: str,
    line: int | None = None,
) -> None:
    diagnostics.append(Diagnostic(code, severity, message, path, line))


def _parse_header(
    lines: list[str],
    spec: LanguageSpec,
    mode: ParseMode,
    source_path: str,
    diagnostics: list[Diagnostic],
) -> tuple[dict[str, str], set[int]]:
    metadata: dict[str, str] = {}
    metadata_indices: set[int] = set()
    key_positions: list[tuple[str, int]] = []

    for index, line in enumerate(lines[:HEADER_SCAN_LIMIT]):
        match = _match_metadata(line, spec)
        if match is None:
            continue

        metadata_indices.add(index)
        key_positions.append((match.key, index))
        if match.key in metadata:
            _diagnostic(
                diagnostics,
                "SOL003",
                "error",
                f"{match.key} 메타데이터가 중복되었습니다.",
                source_path,
                index + 1,
            )
        else:
            metadata[match.key] = match.value

        if not match.canonical:
            severity: Severity = "error" if mode == "strict" else "warning"
            _diagnostic(
                diagnostics,
                "SOL004",
                severity,
                f"메타데이터는 '{spec.line_comment} {match.key}: 값' 형식을 사용해야 합니다.",
                source_path,
                index + 1,
            )
        elif match.prefix != spec.line_comment:
            severity = "error" if mode == "strict" else "warning"
            _diagnostic(
                diagnostics,
                "SOL004",
                severity,
                f"{spec.language} 메타데이터 주석은 '{spec.line_comment}'를 사용해야 합니다.",
                source_path,
                index + 1,
            )

    author = metadata.get("Authored by", "")
    if not author or author == "-":
        line = next((index + 1 for key, index in key_positions if key == "Authored by"), 1)
        _diagnostic(
            diagnostics,
            "SOL002",
            "error",
            "Authored by 값은 필수이며 '-'를 사용할 수 없습니다.",
            source_path,
            line,
        )

    if mode == "strict" and key_positions:
        first_metadata_line = min(index for _, index in key_positions)
        if first_metadata_line != 0:
            _diagnostic(
                diagnostics,
                "SOL004",
                "error",
                "메타데이터 헤더는 파일 첫 줄에서 시작해야 합니다.",
                source_path,
                first_metadata_line + 1,
            )

        expected_order = {key: position for position, key in enumerate(METADATA_KEYS)}
        actual_order = [expected_order[key] for key, _ in key_positions]
        if actual_order != sorted(actual_order):
            _diagnostic(
                diagnostics,
                "SOL004",
                "error",
                "메타데이터 키 순서는 Authored by, Co-authored by, Link 순이어야 합니다.",
                source_path,
                key_positions[0][1] + 1,
            )

        sorted_indices = sorted(metadata_indices)
        if sorted_indices and sorted_indices != list(range(sorted_indices[-1] + 1)):
            _diagnostic(
                diagnostics,
                "SOL004",
                "error",
                "메타데이터 헤더 사이에 빈 줄이나 다른 내용을 넣을 수 없습니다.",
                source_path,
                sorted_indices[0] + 1,
            )

    submission_url = metadata.get("Link", "")
    if submission_url and not _is_http_url(submission_url):
        line = next((index + 1 for key, index in key_positions if key == "Link"), None)
        _diagnostic(
            diagnostics,
            "SOL005",
            "error",
            "Link는 절대 http 또는 https URL이어야 합니다.",
            source_path,
            line,
        )

    return metadata, metadata_indices


def _parse_description(
    lines: list[str],
    spec: LanguageSpec,
    mode: ParseMode,
    source_path: str,
    diagnostics: list[Diagnostic],
) -> tuple[str | None, set[int]]:
    marker_index: int | None = None
    closing_token = "*/"

    for index, line in enumerate(lines):
        content = line.rstrip("\r\n")
        if spec.description_kind == "python":
            marker = re.fullmatch(r"\s*(\"\"\"|''')\s*Solution Description\s*", content)
            if marker:
                marker_index = index
                closing_token = marker.group(1)
        elif re.fullmatch(r"\s*/\*\s*Solution Description\s*", content):
            marker_index = index
            closing_token = "*/"

    if marker_index is None:
        severity: Severity = "error" if mode == "strict" else "warning"
        _diagnostic(
            diagnostics,
            "SOL007",
            severity,
            "Solution Description 블록이 없습니다.",
            source_path,
        )
        return None, set()

    close_pattern = re.compile(rf"\s*{re.escape(closing_token)}\s*")
    closing_index: int | None = None
    for index in range(marker_index + 1, len(lines)):
        if close_pattern.fullmatch(lines[index].rstrip("\r\n")):
            closing_index = index
            break

    if closing_index is None:
        _diagnostic(
            diagnostics,
            "SOL006",
            "error",
            f"Solution Description 블록을 닫는 '{closing_token}'가 없습니다.",
            source_path,
            marker_index + 1,
        )
        return None, set(range(marker_index, len(lines)))

    trailing_line = next(
        (index for index in range(closing_index + 1, len(lines)) if lines[index].strip()),
        None,
    )
    if trailing_line is not None:
        _diagnostic(
            diagnostics,
            "SOL006",
            "error",
            "Solution Description 블록 뒤에는 코드나 주석을 둘 수 없습니다.",
            source_path,
            trailing_line + 1,
        )

    description = "".join(lines[marker_index + 1 : closing_index]).strip()
    return description or None, set(range(marker_index, closing_index + 1))


def parse_solution(path: Path, repository_root: Path, mode: ParseMode = "compat") -> ParseResult:
    input_root = repository_root
    repository_root = input_root.resolve()
    if path.is_absolute():
        try:
            relative_path = path.relative_to(input_root)
        except ValueError:
            relative_path = Path(str(path))
        absolute_path = path
    else:
        relative_path = path
        absolute_path = input_root / path
    diagnostics: list[Diagnostic] = []

    try:
        absolute_path.resolve(strict=False).relative_to(repository_root)
    except ValueError:
        _diagnostic(
            diagnostics,
            "SOL001",
            "error",
            "솔루션 경로가 저장소 밖을 가리킵니다.",
            relative_path.as_posix(),
        )
        return ParseResult(diagnostics=diagnostics)

    source_path = relative_path.as_posix()
    parts = relative_path.parts
    if len(parts) != 4 or parts[0] != "solutions":
        _diagnostic(
            diagnostics,
            "SOL001",
            "error",
            "경로는 solutions/{platform}/{problem_id}/{filename} 형식이어야 합니다.",
            source_path,
        )
        return ParseResult(diagnostics=diagnostics)

    _, platform, problem_id, filename = parts
    if platform not in ALLOWED_PLATFORMS:
        _diagnostic(
            diagnostics,
            "SOL001",
            "error",
            f"지원하지 않는 플랫폼입니다: {platform}",
            source_path,
        )

    if not problem_id.isdigit() or int(problem_id) <= 0:
        _diagnostic(
            diagnostics,
            "SOL001",
            "error",
            "문제 번호는 양의 정수여야 합니다.",
            source_path,
        )

    extension = Path(filename).suffix.lstrip(".")
    spec = LANGUAGE_SPECS.get(extension)
    if spec is None:
        _diagnostic(
            diagnostics,
            "SOL008",
            "error",
            f"지원하지 않는 솔루션 확장자입니다: .{extension}" if extension else "파일 확장자가 없습니다.",
            source_path,
        )
        return ParseResult(diagnostics=diagnostics)

    if not spec.filename_pattern.fullmatch(filename):
        _diagnostic(
            diagnostics,
            "SOL008",
            "error",
            f"{spec.language} 파일명이 허용된 형식이 아닙니다: {filename}",
            source_path,
        )

    if absolute_path.is_symlink():
        _diagnostic(
            diagnostics,
            "SOL009",
            "error",
            "솔루션 파일은 symlink일 수 없습니다.",
            source_path,
        )
        return ParseResult(diagnostics=diagnostics)

    try:
        content = absolute_path.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        _diagnostic(
            diagnostics,
            "SOL009",
            "error",
            "솔루션 파일은 UTF-8 텍스트여야 합니다.",
            source_path,
        )
        return ParseResult(diagnostics=diagnostics)
    except OSError as error:
        _diagnostic(
            diagnostics,
            "SOL009",
            "error",
            f"솔루션 파일을 읽을 수 없습니다: {error}",
            source_path,
        )
        return ParseResult(diagnostics=diagnostics)

    if "\x00" in content:
        _diagnostic(
            diagnostics,
            "SOL009",
            "error",
            "솔루션 파일은 NUL 문자가 없는 일반 UTF-8 텍스트여야 합니다.",
            source_path,
        )
        return ParseResult(diagnostics=diagnostics)

    lines = content.splitlines(keepends=True)
    metadata, metadata_indices = _parse_header(lines, spec, mode, source_path, diagnostics)
    description, description_indices = _parse_description(lines, spec, mode, source_path, diagnostics)

    excluded_indices = metadata_indices | description_indices
    code_lines = _trim_blank_edges(
        [line for index, line in enumerate(lines) if index not in excluded_indices]
    )
    code = "".join(code_lines).rstrip("\r\n")
    if not code.strip():
        _diagnostic(
            diagnostics,
            "SOL010",
            "error",
            "메타데이터와 풀이 설명을 제외한 코드 본문이 비어 있습니다.",
            source_path,
        )

    coauthor_value = metadata.get("Co-authored by", "").strip()
    coauthors = []
    if coauthor_value and coauthor_value != "-":
        coauthors = [item.strip() for item in coauthor_value.split(",") if item.strip()]

    submission_url = metadata.get("Link", "").strip() or None
    solution = ParsedSolution(
        platform=platform,
        problem_id=problem_id,
        filename=filename,
        extension=extension,
        language=spec.language,
        lexer=spec.lexer,
        source_path=source_path,
        author=metadata.get("Authored by", "").strip(),
        coauthors=coauthors,
        submission_url=submission_url,
        code=code,
        solution_description=description,
    )
    return ParseResult(solution=solution, diagnostics=diagnostics)

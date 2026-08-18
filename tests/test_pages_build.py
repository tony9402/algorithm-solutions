from __future__ import annotations

import json
import sys
import tempfile
import unittest
from html.parser import HTMLParser
from pathlib import Path


REPOSITORY_ROOT = Path(__file__).resolve().parents[1]
if str(REPOSITORY_ROOT) not in sys.path:
    sys.path.insert(0, str(REPOSITORY_ROOT))

from pages.build import build_site


class _SourceCodeParser(HTMLParser):
    def __init__(self) -> None:
        super().__init__()
        self.in_source = False
        self.current: list[str] = []
        self.blocks: list[str] = []

    def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
        attributes = dict(attrs)
        if tag == "pre" and "source-code" in (attributes.get("class") or "").split():
            self.in_source = True
            self.current = []

    def handle_endtag(self, tag: str) -> None:
        if tag == "pre" and self.in_source:
            self.blocks.append("".join(self.current))
            self.current = []
            self.in_source = False

    def handle_data(self, data: str) -> None:
        if self.in_source:
            self.current.append(data)


class _DocumentReferenceParser(HTMLParser):
    def __init__(self) -> None:
        super().__init__()
        self.references: list[str] = []
        self.ids: list[str] = []

    def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
        attributes = dict(attrs)
        if attributes.get("id"):
            self.ids.append(attributes["id"])
        for name in ("href", "src"):
            value = attributes.get(name)
            if value:
                self.references.append(value)


class _ProblemCardParser(HTMLParser):
    def __init__(self) -> None:
        super().__init__()
        self.card_count = 0
        self.visible_card_count = 0

    def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
        attributes = dict(attrs)
        if tag != "article" or "problem-card" not in (attributes.get("class") or "").split():
            return
        self.card_count += 1
        if "hidden" not in attributes:
            self.visible_card_count += 1


class PagesBuildTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.temporary_directory = tempfile.TemporaryDirectory()
        cls.output = Path(cls.temporary_directory.name) / "site"
        cls.result = build_site(
            REPOSITORY_ROOT,
            REPOSITORY_ROOT / "pages" / "config.yaml",
            cls.output,
            "/algorithm-solutions",
        )

    @classmethod
    def tearDownClass(cls) -> None:
        cls.temporary_directory.cleanup()

    def test_builds_repository_baseline(self) -> None:
        source_paths = [
            path
            for path in (REPOSITORY_ROOT / "solutions").glob("*/*/*")
            if path.is_file() or path.is_symlink()
        ]
        source_problems = {(path.parts[-3], path.parts[-2]) for path in source_paths}
        self.assertEqual(self.result.solution_count, len(source_paths))
        self.assertEqual(self.result.problem_count, len(source_problems))
        self.assertGreaterEqual(self.result.solution_count, 549)
        self.assertGreaterEqual(self.result.problem_count, 427)
        self.assertTrue((self.output / "index.html").is_file())
        self.assertTrue((self.output / "announcements" / "index.html").is_file())
        self.assertTrue((self.output / "404.html").is_file())
        self.assertTrue((self.output / ".nojekyll").is_file())

    def test_search_index_has_every_problem(self) -> None:
        index = json.loads(
            (self.output / "assets" / "search-index.json").read_text(encoding="utf-8")
        )
        self.assertEqual(len(index), self.result.problem_count)
        self.assertTrue(
            all(
                (
                    self.output
                    / item["url"].removeprefix("/algorithm-solutions/")
                    / "index.html"
                ).is_file()
                for item in index
            )
        )

    def test_project_pages_base_path_is_used(self) -> None:
        index_html = (self.output / "index.html").read_text(encoding="utf-8")
        self.assertIn('href="/algorithm-solutions/assets/site.css"', index_html)
        self.assertIn('href="/algorithm-solutions/problems/baekjoon/1000/"', index_html)
        self.assertIn('href="/algorithm-solutions/announcements/"', index_html)

    def test_catalog_uses_pagination_without_author_search(self) -> None:
        index_html = (self.output / "index.html").read_text(encoding="utf-8")
        parser = _ProblemCardParser()
        parser.feed(index_html)

        self.assertIn('data-page-size="30"', index_html)
        self.assertIn('id="catalog-pagination"', index_html)
        self.assertNotIn('id="author-filter"', index_html)
        self.assertNotIn("data-authors=", index_html)
        self.assertEqual(parser.card_count, self.result.problem_count)
        self.assertEqual(parser.visible_card_count, 30)

        search_index = json.loads(
            (self.output / "assets" / "search-index.json").read_text(encoding="utf-8")
        )
        self.assertTrue(all("authors" not in item for item in search_index))

    def test_metadata_and_description_markers_are_removed_from_code(self) -> None:
        problem_html = (
            self.output / "problems" / "baekjoon" / "1000" / "index.html"
        ).read_text(encoding="utf-8")
        parser = _SourceCodeParser()
        parser.feed(problem_html)

        self.assertEqual(len(parser.blocks), 4)
        for block in parser.blocks:
            self.assertNotIn("Authored by", block)
            self.assertNotIn("Co-authored by", block)
            self.assertNotIn("Solution Description", block)
        self.assertIn('class="solution-description"', problem_html)

    def test_problem_page_contains_all_solution_variants(self) -> None:
        problem_html = (
            self.output / "problems" / "baekjoon" / "16493" / "index.html"
        ).read_text(encoding="utf-8")
        for filename in ("Main.java", "Main2.java", "Main3.java", "Main4.java"):
            self.assertIn(filename, problem_html)

    def test_internal_links_and_document_ids_are_valid(self) -> None:
        base_path = "/algorithm-solutions/"
        for html_path in self.output.rglob("*.html"):
            parser = _DocumentReferenceParser()
            parser.feed(html_path.read_text(encoding="utf-8"))
            self.assertEqual(len(parser.ids), len(set(parser.ids)), f"duplicate id: {html_path}")
            for reference in parser.references:
                if not reference.startswith(base_path):
                    continue
                relative = reference.removeprefix(base_path).split("#", 1)[0]
                target = self.output / relative
                if reference.split("#", 1)[0].endswith("/"):
                    target /= "index.html"
                self.assertTrue(target.is_file(), f"broken link: {html_path}: {reference}")


if __name__ == "__main__":
    unittest.main()

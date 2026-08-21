from __future__ import annotations

import json
import sys
import tempfile
import unittest
from datetime import date
from html.parser import HTMLParser
from pathlib import Path
from unittest import mock


REPOSITORY_ROOT = Path(__file__).resolve().parents[1]
if str(REPOSITORY_ROOT) not in sys.path:
    sys.path.insert(0, str(REPOSITORY_ROOT))

from pages.announcements import Announcement
from pages.build import _community_tier_options, _make_environment, build_site


TEMPLATE_ASSET_PATHS = {
    "favicon": "assets/favicon.test.svg",
    "site_css": "assets/site.test.css",
    "highlight_css": "assets/highlight.test.css",
    "site_js": "assets/site.test.js",
}


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
        with mock.patch.dict("os.environ", {"SITE_BUILD_ID": "test-build-123"}):
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

    def test_community_snapshot_is_published_and_problem_ui_is_rendered(self) -> None:
        source = json.loads(
            (REPOSITORY_ROOT / "community-data" / "discussions.json").read_text(
                encoding="utf-8"
            )
        )
        published = json.loads(
            (self.output / "assets" / "community-data.json").read_text(encoding="utf-8")
        )
        problem_html = (
            self.output / "problems" / "baekjoon" / "1000" / "index.html"
        ).read_text(encoding="utf-8")

        self.assertEqual(published, source)
        self.assertIn('id="community"', problem_html)
        self.assertIn("data-community-vote", problem_html)
        self.assertIn('data-problem="baekjoon/1000"', problem_html)
        self.assertIn("GitHub로 로그인", problem_html)
        self.assertIn("평가 API가 아직 설정되지 않았습니다", problem_html)
        self.assertEqual(problem_html.count('<option value="'), 31)
        configuration = source.get("configuration", {})
        comments_category = configuration.get("comments_category") or {}
        if configuration.get("ready") and comments_category.get("id"):
            self.assertIn('src="https://giscus.app/client.js"', problem_html)
            self.assertIn(
                f'data-repo-id="{configuration["repository_id"]}"', problem_html
            )
            self.assertIn(
                f'data-category-id="{comments_category["id"]}"', problem_html
            )
            self.assertNotIn("Discussion 연동 준비 중", problem_html)
        else:
            self.assertNotIn('src="https://giscus.app/client.js"', problem_html)
            self.assertIn("Discussion 연동 준비 중", problem_html)

    def test_ready_community_configuration_embeds_problem_specific_giscus(self) -> None:
        environment = _make_environment(REPOSITORY_ROOT / "pages" / "templates", "")
        rendered = environment.get_template("problem.html").render(
            site={
                "description": "test",
                "repository_url": "https://github.com/example/repository",
            },
            page_title="테스트 문제",
            active_nav="solutions",
            build_id="test-build",
            asset_paths=TEMPLATE_ASSET_PATHS,
            problem_count=1,
            solution_count=1,
            recent_announcement_ids=[],
            community_repository="example/repository",
            community_generated_at="2026-08-20T00:00:00Z",
            community_vote_api_url="https://community.example.workers.dev",
            community_tier_options=_community_tier_options(),
            community_config={
                "repository_id": "R_repo",
                "comments_category": {
                    "id": "DIC_comments",
                    "name": "Announcements",
                    "slug": "announcements",
                },
                "ready": True,
            },
            community={
                "difficulty": {
                    "vote_count": 2,
                    "mean_value": 13.5,
                    "representative": {
                        "value": 14,
                        "name": "Gold II",
                        "group": "gold",
                    },
                    "distribution": {"Gold III": 1, "Gold II": 1},
                },
                "recommendation": {
                    "recommended": 1,
                    "not_recommended": 1,
                    "score": 0,
                    "recommended_percent": 50,
                },
                "comments": {
                    "discussion_url": "https://github.com/example/repository/discussions/10",
                    "comment_count": 3,
                },
            },
            problem={
                "key": "baekjoon/1000",
                "platform": "baekjoon",
                "platform_label": "Baekjoon",
                "problem_id": "1000",
                "title": "A+B",
                "solution_count": 0,
                "languages": [],
                "external_url": "https://www.acmicpc.net/problem/1000",
                "solutions": [],
            },
        )

        self.assertIn('src="https://giscus.app/client.js"', rendered)
        self.assertNotIn('name="recommendation" value="up" required', rendered)
        self.assertNotIn('name="recommendation" value="down" required', rendered)
        self.assertIn('data-repo-id="R_repo"', rendered)
        self.assertIn('data-category-id="DIC_comments"', rendered)
        self.assertIn('data-term="problem:baekjoon/1000"', rendered)
        self.assertIn('data-api-url="https://community.example.workers.dev"', rendered)
        self.assertIn('<option value="30">Ruby I</option>', rendered)
        self.assertIn("Gold II", rendered)
        self.assertIn("GitHub에서 댓글 3개 보기", rendered)
        self.assertNotIn("Discussion 연동 준비 중", rendered)

    def test_project_pages_base_path_is_used(self) -> None:
        index_html = (self.output / "index.html").read_text(encoding="utf-8")
        self.assertRegex(
            index_html,
            r'href="/algorithm-solutions/assets/site\.[0-9a-f]{12}\.css"',
        )
        self.assertIn('href="/algorithm-solutions/problems/baekjoon/1000/"', index_html)
        self.assertIn('href="/algorithm-solutions/announcements/"', index_html)

    def test_pages_embed_build_id_and_fingerprinted_assets(self) -> None:
        index_html = (self.output / "index.html").read_text(encoding="utf-8")
        self.assertIn('<meta name="site-build-id" content="test-build-123">', index_html)
        self.assertRegex(index_html, r'/assets/site\.[0-9a-f]{12}\.css')
        self.assertRegex(index_html, r'/assets/highlight\.[0-9a-f]{12}\.css')
        self.assertRegex(index_html, r'/assets/site\.[0-9a-f]{12}\.js')
        self.assertRegex(index_html, r'/assets/favicon\.[0-9a-f]{12}\.svg')
        self.assertTrue((self.output / "assets" / "site.css").is_file())
        self.assertTrue((self.output / "assets" / "site.js").is_file())
        self.assertIn("this.href='/algorithm-solutions/assets/site.css'", index_html)
        self.assertIn("this.src='/algorithm-solutions/assets/site.js'", index_html)

    def test_announcements_render_as_closed_collapsible_title_list(self) -> None:
        environment = _make_environment(REPOSITORY_ROOT / "pages" / "templates", "")
        rendered = environment.get_template("announcements.html").render(
            site={
                "description": "test",
                "repository_url": "https://github.com/example/repository",
            },
            page_title="공지사항",
            active_nav="announcements",
            build_id="test-build",
            asset_paths=TEMPLATE_ASSET_PATHS,
            problem_count=1,
            solution_count=1,
            recent_announcement_ids=["test-notice"],
            announcements=[
                Announcement(
                    announcement_id="test-notice",
                    title="테스트 공지",
                    published_at=date(2026, 8, 18),
                    published_label="2026. 08. 18.",
                    body_html="<p>테스트 본문</p>",
                    is_recent=True,
                )
            ],
        )

        details = '<details id="notice-test-notice" class="announcement-card">'
        self.assertIn(details, rendered)
        self.assertNotIn(f"{details[:-1]} open>", rendered)
        self.assertIn('<summary class="announcement-summary">', rendered)
        self.assertLess(rendered.index("테스트 공지"), rendered.index("테스트 본문"))

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

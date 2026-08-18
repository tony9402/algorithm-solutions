from __future__ import annotations

import tempfile
import unittest
from datetime import date
from pathlib import Path


from pages.announcements import AnnouncementError, load_announcements


class AnnouncementTest(unittest.TestCase):
    def setUp(self) -> None:
        self.temporary_directory = tempfile.TemporaryDirectory()
        self.directory = Path(self.temporary_directory.name)

    def tearDown(self) -> None:
        self.temporary_directory.cleanup()

    def write_announcement(self, filename: str, source: str) -> None:
        (self.directory / filename).write_text(source, encoding="utf-8")

    def test_loads_newest_first_and_marks_only_last_seven_days_recent(self) -> None:
        self.write_announcement(
            "recent.md",
            "---\ntitle: 최근 공지\ndate: 2026-08-17\n---\n\n최근 본문\n",
        )
        self.write_announcement(
            "seven-days-old.md",
            "---\ntitle: 지난 공지\ndate: 2026-08-11\n---\n\n지난 본문\n",
        )

        announcements = load_announcements(
            self.directory,
            today=date(2026, 8, 18),
            recent_days=7,
        )

        self.assertEqual(
            [item.announcement_id for item in announcements],
            ["recent", "seven-days-old"],
        )
        self.assertTrue(announcements[0].is_recent)
        self.assertFalse(announcements[1].is_recent)

    def test_escapes_html_and_removes_unsafe_link_destination(self) -> None:
        self.write_announcement(
            "safe-output.md",
            "---\ntitle: 안전한 출력\ndate: 2026-08-18\n---\n\n"
            "<script>alert('x')</script>\n\n"
            "[위험](javascript:alert(1)) [공식 사이트](https://example.com)\n",
        )

        announcement = load_announcements(
            self.directory,
            today=date(2026, 8, 18),
        )[0]

        self.assertNotIn("<script>", announcement.body_html)
        self.assertIn("&lt;script&gt;", announcement.body_html)
        self.assertNotIn("javascript:", announcement.body_html)
        self.assertIn('href="https://example.com"', announcement.body_html)
        self.assertIn('rel="noopener noreferrer"', announcement.body_html)

    def test_ignores_readme(self) -> None:
        self.write_announcement("README.md", "작성 안내")
        self.assertEqual(
            load_announcements(self.directory, today=date(2026, 8, 18)),
            [],
        )

    def test_rejects_future_date(self) -> None:
        self.write_announcement(
            "future.md",
            "---\ntitle: 미래 공지\ndate: 2026-08-19\n---\n\n본문\n",
        )
        with self.assertRaisesRegex(AnnouncementError, "미래 날짜"):
            load_announcements(self.directory, today=date(2026, 8, 18))

    def test_rejects_invalid_filename(self) -> None:
        self.write_announcement(
            "Invalid_Name.md",
            "---\ntitle: 공지\ndate: 2026-08-18\n---\n\n본문\n",
        )
        with self.assertRaisesRegex(AnnouncementError, "파일명"):
            load_announcements(self.directory, today=date(2026, 8, 18))


if __name__ == "__main__":
    unittest.main()

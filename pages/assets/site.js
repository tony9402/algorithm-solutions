(() => {
    "use strict";

    const normalise = (value) => value.trim().toLocaleLowerCase();

    const filters = document.querySelector("#solution-filters");
    if (filters) {
        const query = document.querySelector("#query-filter");
        const platform = document.querySelector("#platform-filter");
        const language = document.querySelector("#language-filter");
        const cards = [...document.querySelectorAll("[data-problem-card]")];
        const count = document.querySelector("#result-count");
        const empty = document.querySelector("#empty-state");
        const pagination = document.querySelector("#catalog-pagination");
        const catalogHeading = document.querySelector("#catalog-heading");
        const configuredPageSize = Number.parseInt(filters.dataset.pageSize, 10);
        const pageSize = Number.isInteger(configuredPageSize) && configuredPageSize > 0
            ? configuredPageSize
            : 30;
        let currentPage = 1;

        const pageFromUrl = () => {
            const value = Number.parseInt(new URLSearchParams(window.location.search).get("page"), 10);
            return Number.isInteger(value) && value > 0 ? value : 1;
        };

        const updatePageUrl = (page, mode) => {
            const url = new URL(window.location.href);
            if (page > 1) url.searchParams.set("page", String(page));
            else url.searchParams.delete("page");
            history[mode === "push" ? "pushState" : "replaceState"](null, "", url);
        };

        const pageButton = (label, page, options = {}) => {
            const button = document.createElement("button");
            button.type = "button";
            button.className = "pagination-button";
            button.textContent = label;
            button.dataset.page = String(page);
            if (options.current) {
                button.classList.add("is-current");
                button.setAttribute("aria-current", "page");
            }
            if (options.label) button.setAttribute("aria-label", options.label);
            if (options.disabled) button.disabled = true;
            return button;
        };

        const renderPagination = (pageCount) => {
            pagination.replaceChildren();
            pagination.hidden = pageCount <= 1;
            if (pageCount <= 1) return;

            pagination.append(pageButton("이전", currentPage - 1, {
                disabled: currentPage === 1,
                label: "이전 페이지",
            }));

            const candidates = new Set([1, pageCount]);
            for (let page = currentPage - 2; page <= currentPage + 2; page += 1) {
                if (page >= 1 && page <= pageCount) candidates.add(page);
            }
            const pages = [...candidates].sort((left, right) => left - right);
            pages.forEach((page, index) => {
                if (index > 0 && page - pages[index - 1] > 1) {
                    const ellipsis = document.createElement("span");
                    ellipsis.className = "pagination-ellipsis";
                    ellipsis.textContent = "…";
                    ellipsis.setAttribute("aria-hidden", "true");
                    pagination.append(ellipsis);
                }
                pagination.append(pageButton(String(page), page, {
                    current: page === currentPage,
                    label: `${page}페이지`,
                }));
            });

            pagination.append(pageButton("다음", currentPage + 1, {
                disabled: currentPage === pageCount,
                label: "다음 페이지",
            }));
        };

        const applyFilters = ({ requestedPage = 1, historyMode = "replace" } = {}) => {
            const queryValue = normalise(query.value);
            const platformValue = platform.value;
            const languageValue = normalise(language.value);
            const matches = cards.filter((card) => {
                const matchesQuery = !queryValue || card.dataset.search.includes(queryValue);
                const matchesPlatform = !platformValue || card.dataset.platform === platformValue;
                const languages = card.dataset.languages.split("|");
                const matchesLanguage = !languageValue || languages.includes(languageValue);
                return matchesQuery && matchesPlatform && matchesLanguage;
            });
            const pageCount = Math.max(1, Math.ceil(matches.length / pageSize));
            currentPage = Math.min(Math.max(requestedPage, 1), pageCount);
            const visibleCards = new Set(
                matches.slice((currentPage - 1) * pageSize, currentPage * pageSize)
            );
            cards.forEach((card) => {
                card.hidden = !visibleCards.has(card);
            });

            count.textContent = matches.length === 0
                ? "0개 문제"
                : `${matches.length}개 문제 · ${currentPage}/${pageCount} 페이지`;
            empty.hidden = matches.length !== 0;
            renderPagination(matches.length === 0 ? 0 : pageCount);
            updatePageUrl(currentPage, historyMode);
        };

        filters.addEventListener("input", () => applyFilters());
        filters.addEventListener("change", () => applyFilters());
        filters.addEventListener("reset", () => window.setTimeout(() => applyFilters()));
        document.querySelector("[data-reset-filters]")?.addEventListener("click", () => {
            filters.reset();
            applyFilters();
            query.focus();
        });
        pagination.addEventListener("click", (event) => {
            const button = event.target.closest("[data-page]");
            if (!button || button.disabled) return;
            applyFilters({ requestedPage: Number.parseInt(button.dataset.page, 10), historyMode: "push" });
            catalogHeading.scrollIntoView({ behavior: "smooth", block: "start" });
        });
        window.addEventListener("popstate", () => {
            applyFilters({ requestedPage: pageFromUrl(), historyMode: "replace" });
        });
        applyFilters({ requestedPage: pageFromUrl(), historyMode: "replace" });
    }

    const announcementLink = document.querySelector("[data-announcement-link]");
    const noticeIndicator = document.querySelector("[data-notice-indicator]");
    if (announcementLink && noticeIndicator) {
        const recentIds = announcementLink.dataset.recentAnnouncementIds.split(",").filter(Boolean);
        const storageKey = "algorithm-solutions-seen-announcements-v1";
        try {
            const testKey = `${storageKey}-test`;
            localStorage.setItem(testKey, "1");
            localStorage.removeItem(testKey);
            const stored = JSON.parse(localStorage.getItem(storageKey) || "[]");
            const seenIds = new Set(Array.isArray(stored) ? stored.filter((id) => typeof id === "string") : []);

            if (document.body.dataset.page === "announcements") {
                recentIds.forEach((id) => seenIds.add(id));
                localStorage.setItem(storageKey, JSON.stringify([...seenIds]));
            } else {
                const unseenCount = recentIds.filter((id) => !seenIds.has(id)).length;
                noticeIndicator.hidden = unseenCount === 0;
                if (unseenCount > 0) {
                    noticeIndicator.textContent = unseenCount > 9 ? "9+" : String(unseenCount);
                    noticeIndicator.setAttribute("aria-label", `읽지 않은 새 공지 ${unseenCount}개`);
                }
            }
        } catch {
            noticeIndicator.hidden = true;
        }
    }

    const tabButtons = [...document.querySelectorAll("[data-solution-tab]")];
    const panels = [...document.querySelectorAll(".solution-panel")];
    if (tabButtons.length > 0) {
        const activate = (targetId, updateHash = true) => {
            const activeButton = tabButtons.find((button) => button.dataset.solutionTab === targetId);
            const activePanel = panels.find((panel) => panel.id === targetId);
            if (!activeButton || !activePanel) return;

            tabButtons.forEach((button) => {
                const selected = button === activeButton;
                button.setAttribute("aria-selected", String(selected));
                button.tabIndex = selected ? 0 : -1;
            });
            panels.forEach((panel) => {
                panel.hidden = panel !== activePanel;
            });
            if (updateHash) history.replaceState(null, "", `#${targetId}`);
        };

        tabButtons.forEach((button, index) => {
            button.addEventListener("click", () => activate(button.dataset.solutionTab));
            button.addEventListener("keydown", (event) => {
                if (!["ArrowLeft", "ArrowRight", "Home", "End"].includes(event.key)) return;
                event.preventDefault();
                let nextIndex = index;
                if (event.key === "ArrowLeft") nextIndex = (index - 1 + tabButtons.length) % tabButtons.length;
                if (event.key === "ArrowRight") nextIndex = (index + 1) % tabButtons.length;
                if (event.key === "Home") nextIndex = 0;
                if (event.key === "End") nextIndex = tabButtons.length - 1;
                const next = tabButtons[nextIndex];
                activate(next.dataset.solutionTab);
                next.focus();
            });
        });

        const hashTarget = decodeURIComponent(window.location.hash.slice(1));
        if (hashTarget) activate(hashTarget, false);
    }

    document.querySelectorAll("[data-copy-code]").forEach((button) => {
        button.addEventListener("click", async () => {
            const code = button.closest(".code-section")?.querySelector("code")?.textContent ?? "";
            const original = button.textContent;
            try {
                await navigator.clipboard.writeText(code);
                button.textContent = "복사됨";
            } catch {
                button.textContent = "복사 실패";
            }
            window.setTimeout(() => {
                button.textContent = original;
            }, 1600);
        });
    });
})();

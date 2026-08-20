(() => {
    "use strict";

    const normalise = (value) => value.trim().toLocaleLowerCase();
    const copyText = async (value) => {
        try {
            await navigator.clipboard.writeText(value);
            return true;
        } catch {
            const textarea = document.createElement("textarea");
            textarea.value = value;
            textarea.setAttribute("readonly", "");
            textarea.style.position = "fixed";
            textarea.style.opacity = "0";
            document.body.append(textarea);
            textarea.select();
            const copied = document.execCommand("copy");
            textarea.remove();
            return copied;
        }
    };

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

    const votePanel = document.querySelector("[data-community-vote]");
    if (votePanel) {
        const apiUrl = votePanel.dataset.apiUrl.replace(/\/$/, "");
        const problem = votePanel.dataset.problem;
        const loginButton = votePanel.querySelector("[data-community-login]");
        const logoutButton = votePanel.querySelector("[data-community-logout]");
        const userBox = votePanel.querySelector("[data-community-user]");
        const avatar = votePanel.querySelector("[data-community-avatar]");
        const loginName = votePanel.querySelector("[data-community-login-name]");
        const form = votePanel.querySelector("[data-community-vote-form]");
        const fields = votePanel.querySelector("[data-community-vote-fields]");
        const status = votePanel.querySelector("[data-community-vote-status]");
        const submitButton = form.querySelector("[type='submit']");
        const sessionKey = "algorithm-solutions-community-session-v1";
        let sessionToken = sessionStorage.getItem(sessionKey) || "";
        let oauthError = "";

        const setStatus = (message, tone = "") => {
            status.textContent = message;
            if (tone) status.dataset.tone = tone;
            else delete status.dataset.tone;
        };

        const setUser = (user) => {
            const authenticated = Boolean(user);
            loginButton.hidden = authenticated;
            userBox.hidden = !authenticated;
            fields.disabled = !authenticated;
            if (!authenticated) return;
            avatar.src = user.avatarUrl || "";
            avatar.alt = `${user.login} 프로필 이미지`;
            loginName.textContent = user.login;
        };

        const apiRequest = async (path, options = {}) => {
            const headers = new Headers(options.headers || {});
            if (sessionToken) headers.set("Authorization", `Bearer ${sessionToken}`);
            const response = await fetch(`${apiUrl}${path}`, {...options, headers});
            const payload = await response.json().catch(() => ({}));
            if (!response.ok) {
                const error = new Error(payload.error || "커뮤니티 API 요청에 실패했습니다.");
                error.status = response.status;
                throw error;
            }
            return payload;
        };

        const oauthParameters = new URLSearchParams(window.location.hash.slice(1));
        if (oauthParameters.has("community_session")) {
            sessionToken = oauthParameters.get("community_session") || "";
            sessionStorage.setItem(sessionKey, sessionToken);
            history.replaceState(null, "", `${window.location.pathname}${window.location.search}#community`);
        } else if (oauthParameters.has("community_error")) {
            oauthError = oauthParameters.get("community_error") || "GitHub 로그인에 실패했습니다.";
            setStatus(oauthError, "error");
            history.replaceState(null, "", `${window.location.pathname}${window.location.search}#community`);
        }

        loginButton.addEventListener("click", () => {
            if (!apiUrl) return;
            const returnUrl = new URL(window.location.href);
            returnUrl.hash = "";
            const authUrl = new URL(`${apiUrl}/auth/start`);
            authUrl.searchParams.set("return_to", returnUrl.toString());
            window.location.assign(authUrl.toString());
        });

        logoutButton.addEventListener("click", async () => {
            try {
                await apiRequest("/logout", {method: "POST"});
            } catch {
                // 로컬 세션은 API 응답과 관계없이 제거한다.
            }
            sessionToken = "";
            sessionStorage.removeItem(sessionKey);
            setUser(null);
            setStatus("로그아웃했습니다. 평가하려면 다시 로그인해 주세요.");
        });

        form.addEventListener("submit", async (event) => {
            event.preventDefault();
            if (!sessionToken || !form.reportValidity()) return;
            const formData = new FormData(form);
            submitButton.disabled = true;
            const original = submitButton.textContent;
            submitButton.textContent = "저장 중…";
            setStatus("평가를 저장하고 있습니다.");
            try {
                const result = await apiRequest("/vote", {
                    method: "POST",
                    headers: {"Content-Type": "application/json"},
                    body: JSON.stringify({
                        problem,
                        difficulty: Number(formData.get("difficulty")),
                        recommendation: formData.get("recommendation"),
                    }),
                });
                setStatus(
                    `${result.vote.difficultyName} · ${result.vote.recommendation === "up" ? "추천" : "비추천"}으로 저장했습니다. 집계는 다음 동기화 때 반영됩니다.`,
                    "success",
                );
            } catch (error) {
                if (error.status === 401) {
                    sessionToken = "";
                    sessionStorage.removeItem(sessionKey);
                    setUser(null);
                }
                setStatus(error.message, "error");
            } finally {
                submitButton.disabled = false;
                submitButton.textContent = original;
            }
        });

        const initialiseVotePanel = async () => {
            if (!apiUrl) {
                setUser(null);
                return;
            }
            if (!sessionToken) {
                setUser(null);
                if (!oauthError) setStatus("평가하려면 GitHub로 로그인해 주세요.");
                return;
            }
            try {
                const session = await apiRequest("/session");
                setUser(session.user);
                setStatus(`${session.user.login} 계정으로 로그인했습니다.`);
            } catch (error) {
                sessionToken = "";
                sessionStorage.removeItem(sessionKey);
                setUser(null);
                setStatus(error.message, "error");
            }
        };

        initialiseVotePanel();
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
            button.textContent = await copyText(code) ? "복사됨" : "복사 실패";
            window.setTimeout(() => {
                button.textContent = original;
            }, 1600);
        });
    });

    document.querySelectorAll("[data-copy-value]").forEach((button) => {
        button.addEventListener("click", async () => {
            const original = button.textContent;
            button.textContent = await copyText(button.dataset.copyValue || "")
                ? "복사됨"
                : "복사 실패";
            window.setTimeout(() => {
                button.textContent = original;
            }, 1600);
        });
    });
})();

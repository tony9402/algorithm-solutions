import assert from "node:assert/strict";
import test from "node:test";

import {
    buildDiscussionBody,
    parseAllowedOrigins,
    tierName,
    validateReturnUrl,
    validateVote,
} from "../src/index.js";
import worker from "../src/index.js";


class MemoryKv {
    constructor(entries = {}) {
        this.values = new Map(Object.entries(entries));
    }

    async get(key, type) {
        const value = this.values.get(key);
        if (value === undefined) return null;
        return type === "json" ? JSON.parse(value) : value;
    }

    async put(key, value) {
        this.values.set(key, value);
    }

    async delete(key) {
        this.values.delete(key);
    }
}


const workerEnv = (kv = new MemoryKv()) => ({
    GITHUB_CLIENT_ID: "Iv1.test",
    GITHUB_CLIENT_SECRET: "secret",
    GITHUB_REPOSITORY: "example/repository",
    RATINGS_CATEGORY: "General",
    ALLOWED_ORIGINS: "https://example.github.io,http://127.0.0.1:8765",
    SITE_URL: "https://example.github.io/repository",
    COMMUNITY_KV: kv,
});


test("solved.ac 30단계 이름을 변환한다", () => {
    assert.equal(tierName(1), "Bronze V");
    assert.equal(tierName(5), "Bronze I");
    assert.equal(tierName(6), "Silver V");
    assert.equal(tierName(30), "Ruby I");
    assert.throws(() => tierName(31));
});


test("웹 평가 payload를 검증한다", () => {
    assert.deepEqual(
        validateVote({problem: "Baekjoon/1000", difficulty: 13, recommendation: "up"}),
        {
            problem: "baekjoon/1000",
            difficulty: 13,
            difficultyName: "Gold III",
            recommendation: "up",
        },
    );
    assert.throws(() => validateVote({problem: "../secret", difficulty: 13, recommendation: "up"}));
    assert.throws(() => validateVote({problem: "baekjoon/1000", difficulty: 0, recommendation: "up"}));
    assert.throws(() => validateVote({problem: "baekjoon/1000", difficulty: 13, recommendation: "maybe"}));
});


test("허용된 사이트로만 OAuth 복귀를 허용한다", () => {
    const origins = parseAllowedOrigins("https://example.github.io,http://127.0.0.1:8765");
    assert.equal(
        validateReturnUrl("https://example.github.io/repo/problems/baekjoon/1000/#community", origins),
        "https://example.github.io/repo/problems/baekjoon/1000/",
    );
    assert.throws(() => validateReturnUrl("https://attacker.example/", origins));
});


test("Discussion 집계기가 읽을 수 있는 본문을 만든다", () => {
    const body = buildDiscussionBody(
        validateVote({problem: "baekjoon/1000", difficulty: 13, recommendation: "down"}),
        "https://example.github.io/repo",
    );
    assert.match(body, /algorithm-solutions-rating:v1/);
    assert.match(body, /### 문제 식별자\n\nbaekjoon\/1000/);
    assert.match(body, /### 체감 난이도\n\nGold III/);
    assert.match(body, /### 추천 여부\n\n비추천/);
});


test("GitHub App 로그인은 state와 PKCE를 사용하고 넓은 OAuth scope를 요청하지 않는다", async () => {
    const kv = new MemoryKv();
    const response = await worker.fetch(
        new Request(
            "https://community.example.workers.dev/auth/start"
            + "?return_to=https%3A%2F%2Fexample.github.io%2Frepository%2Fproblems%2Fbaekjoon%2F1000%2F",
        ),
        workerEnv(kv),
    );

    assert.equal(response.status, 302);
    const location = new URL(response.headers.get("Location"));
    assert.equal(location.origin, "https://github.com");
    assert.equal(location.pathname, "/login/oauth/authorize");
    assert.equal(location.searchParams.get("client_id"), "Iv1.test");
    assert.equal(location.searchParams.get("code_challenge_method"), "S256");
    assert.ok(location.searchParams.get("code_challenge"));
    assert.equal(location.searchParams.has("scope"), false);
    const state = location.searchParams.get("state");
    assert.ok(state);
    const stored = JSON.parse(kv.values.get(`oauth-state:${state}`));
    assert.equal(stored.callbackUrl, "https://community.example.workers.dev/auth/callback");
    assert.ok(stored.codeVerifier);
});


test("CORS preflight는 secret이 없어도 처리한다", async () => {
    const response = await worker.fetch(
        new Request("https://community.example.workers.dev/vote", {
            method: "OPTIONS",
            headers: {Origin: "https://example.github.io"},
        }),
        {ALLOWED_ORIGINS: "https://example.github.io"},
    );

    assert.equal(response.status, 204);
    assert.equal(response.headers.get("Access-Control-Allow-Origin"), "https://example.github.io");
});


test("웹 평가를 로그인 사용자 명의의 Discussion으로 저장한다", async () => {
    const kv = new MemoryKv({
        "session:web-session": JSON.stringify({
            accessToken: "ghu_user_token",
            accessTokenExpiresAt: null,
            refreshToken: null,
            refreshTokenExpiresAt: null,
            user: {id: 1, login: "octocat", avatarUrl: "", profileUrl: ""},
        }),
    });
    const originalFetch = globalThis.fetch;
    const calls = [];
    globalThis.fetch = async (_url, options) => {
        calls.push(JSON.parse(options.body));
        if (calls.length === 1) {
            return Response.json({
                data: {
                    repository: {
                        id: "R_repo",
                        discussionCategories: {nodes: [{id: "DIC_general", name: "General"}]},
                    },
                },
            });
        }
        return Response.json({
            data: {
                createDiscussion: {
                    discussion: {
                        id: "D_discussion",
                        number: 42,
                        url: "https://github.com/example/repository/discussions/42",
                    },
                },
            },
        });
    };

    try {
        const response = await worker.fetch(
            new Request("https://community.example.workers.dev/vote", {
                method: "POST",
                headers: {
                    Authorization: "Bearer web-session",
                    "Content-Type": "application/json",
                    Origin: "https://example.github.io",
                },
                body: JSON.stringify({
                    problem: "baekjoon/1000",
                    difficulty: 13,
                    recommendation: "up",
                }),
            }),
            workerEnv(kv),
        );
        const payload = await response.json();

        assert.equal(response.status, 200);
        assert.equal(payload.user.login, "octocat");
        assert.equal(payload.vote.difficultyName, "Gold III");
        assert.equal(payload.vote.recommendation, "up");
        assert.match(calls[1].variables.input.body, /baekjoon\/1000/);
        assert.match(calls[1].variables.input.body, /Gold III/);
        assert.ok(kv.values.has("vote:1:baekjoon/1000"));
    } finally {
        globalThis.fetch = originalFetch;
    }
});

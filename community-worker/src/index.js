const GITHUB_API_URL = "https://api.github.com";
const GITHUB_GRAPHQL_URL = "https://api.github.com/graphql";
const GITHUB_AUTHORIZE_URL = "https://github.com/login/oauth/authorize";
const GITHUB_TOKEN_URL = "https://github.com/login/oauth/access_token";
const API_VERSION = "2026-03-10";
const COMMUNITY_API_VERSION = 2;
const OAUTH_STATE_TTL_SECONDS = 10 * 60;
const SESSION_TTL_SECONDS = 30 * 24 * 60 * 60;
const VOTE_RATE_LIMIT_SECONDS = 60;
const TOKEN_REFRESH_MARGIN_MS = 5 * 60 * 1000;
const PROBLEM_PATTERN = /^[a-z0-9-]+\/[1-9][0-9]*$/;
const TIER_GROUPS = ["Bronze", "Silver", "Gold", "Platinum", "Diamond", "Ruby"];
const TIER_RANKS = ["V", "IV", "III", "II", "I"];


class HttpError extends Error {
    constructor(status, message) {
        super(message);
        this.status = status;
    }
}


class GitHubApiError extends Error {
    constructor(message, details = []) {
        super(message);
        this.details = details;
    }
}


export const tierName = (value) => {
    if (!Number.isInteger(value) || value < 1 || value > 30) {
        throw new HttpError(400, "난이도 값은 1부터 30까지여야 합니다.");
    }
    const zeroBased = value - 1;
    return `${TIER_GROUPS[Math.floor(zeroBased / 5)]} ${TIER_RANKS[zeroBased % 5]}`;
};


const normaliseProblem = (value) => {
    const problem = String(value || "").trim().toLowerCase();
    if (!PROBLEM_PATTERN.test(problem)) {
        throw new HttpError(400, "문제 식별자가 올바르지 않습니다.");
    }
    return problem;
};


export const parseAllowedOrigins = (value) => new Set(
    String(value || "")
        .split(",")
        .map((item) => item.trim())
        .filter(Boolean)
);


export const validateReturnUrl = (value, allowedOrigins) => {
    let url;
    try {
        url = new URL(value);
    } catch {
        throw new HttpError(400, "로그인 후 돌아갈 주소가 올바르지 않습니다.");
    }
    if (!allowedOrigins.has(url.origin)) {
        throw new HttpError(400, "허용되지 않은 로그인 복귀 주소입니다.");
    }
    if (!new Set(["http:", "https:"]).has(url.protocol)) {
        throw new HttpError(400, "로그인 복귀 주소는 HTTP(S)여야 합니다.");
    }
    url.hash = "";
    return url.toString();
};


export const validateVote = (payload) => {
    const problem = normaliseProblem(payload?.problem);
    const difficulty = Number(payload?.difficulty);
    const recommendation = payload?.recommendation == null
        ? null
        : String(payload.recommendation).trim() || null;
    const difficultyName = tierName(difficulty);
    if (recommendation !== null && !new Set(["up", "down"]).has(recommendation)) {
        throw new HttpError(400, "추천 여부 값이 올바르지 않습니다.");
    }
    return {problem, difficulty, difficultyName, recommendation};
};


export const buildDiscussionBody = (vote, siteUrl) => {
    const recommendationLabel = vote.recommendation === "up"
        ? "추천"
        : vote.recommendation === "down" ? "비추천" : "선택 안 함";
    const problemUrl = `${String(siteUrl || "").replace(/\/$/, "")}/problems/${vote.problem}/`;
    return `<!-- algorithm-solutions-rating:v1 -->

### 문제 식별자

${vote.problem}

### 체감 난이도

${vote.difficultyName}

### 추천 여부

${recommendationLabel}

### 문제 페이지

${problemUrl}
`;
};


const randomToken = () => {
    const bytes = new Uint8Array(32);
    crypto.getRandomValues(bytes);
    return btoa(String.fromCharCode(...bytes))
        .replaceAll("+", "-")
        .replaceAll("/", "_")
        .replaceAll("=", "");
};


const pkceChallenge = async (verifier) => {
    const digest = await crypto.subtle.digest(
        "SHA-256",
        new TextEncoder().encode(verifier),
    );
    return btoa(String.fromCharCode(...new Uint8Array(digest)))
        .replaceAll("+", "-")
        .replaceAll("/", "_")
        .replaceAll("=", "");
};


const jsonResponse = (request, env, data, status = 200) => new Response(
    JSON.stringify(data),
    {
        status,
        headers: {
            "Content-Type": "application/json; charset=utf-8",
            ...corsHeaders(request, env),
        },
    },
);


const corsHeaders = (request, env) => {
    const origin = request.headers.get("Origin");
    const allowedOrigins = parseAllowedOrigins(env.ALLOWED_ORIGINS);
    if (!origin || !allowedOrigins.has(origin)) return {"Vary": "Origin"};
    return {
        "Access-Control-Allow-Origin": origin,
        "Access-Control-Allow-Headers": "Authorization, Content-Type",
        "Access-Control-Allow-Methods": "GET, POST, OPTIONS",
        "Access-Control-Max-Age": "86400",
        "Vary": "Origin",
    };
};


const requireConfiguration = (env) => {
    for (const name of ["GITHUB_CLIENT_ID", "GITHUB_CLIENT_SECRET", "GITHUB_REPOSITORY", "ALLOWED_ORIGINS"]) {
        if (!env[name]) throw new HttpError(503, `Worker 설정이 누락되었습니다: ${name}`);
    }
    if (!env.COMMUNITY_KV) {
        throw new HttpError(503, "Worker KV binding이 누락되었습니다: COMMUNITY_KV");
    }
};


const callbackUrl = (request) => {
    const url = new URL(request.url);
    return `${url.origin}/auth/callback`;
};


const redirectWithError = (returnTo, message) => {
    const url = new URL(returnTo);
    url.hash = new URLSearchParams({community_error: message}).toString();
    return Response.redirect(url.toString(), 302);
};


const handleAuthStart = async (request, env) => {
    const requestUrl = new URL(request.url);
    const returnTo = validateReturnUrl(
        requestUrl.searchParams.get("return_to") || "",
        parseAllowedOrigins(env.ALLOWED_ORIGINS),
    );
    const state = randomToken();
    const codeVerifier = randomToken();
    await env.COMMUNITY_KV.put(
        `oauth-state:${state}`,
        JSON.stringify({returnTo, callbackUrl: callbackUrl(request), codeVerifier}),
        {expirationTtl: OAUTH_STATE_TTL_SECONDS},
    );
    const authorizeUrl = new URL(GITHUB_AUTHORIZE_URL);
    authorizeUrl.searchParams.set("client_id", env.GITHUB_CLIENT_ID);
    authorizeUrl.searchParams.set("redirect_uri", callbackUrl(request));
    authorizeUrl.searchParams.set("state", state);
    authorizeUrl.searchParams.set("code_challenge", await pkceChallenge(codeVerifier));
    authorizeUrl.searchParams.set("code_challenge_method", "S256");
    return Response.redirect(authorizeUrl.toString(), 302);
};


const tokenLifetime = (seconds) => {
    const parsed = Number(seconds);
    return Number.isFinite(parsed) && parsed > 0 ? Date.now() + (parsed * 1000) : null;
};


const normaliseTokenResponse = (payload) => ({
    accessToken: payload.access_token,
    accessTokenExpiresAt: tokenLifetime(payload.expires_in),
    refreshToken: payload.refresh_token || null,
    refreshTokenExpiresAt: tokenLifetime(payload.refresh_token_expires_in),
});


const requestToken = async (parameters, env) => {
    const response = await fetch(GITHUB_TOKEN_URL, {
        method: "POST",
        headers: {
            "Accept": "application/json",
            "Content-Type": "application/x-www-form-urlencoded",
        },
        body: new URLSearchParams(parameters),
    });
    const payload = await response.json();
    if (!response.ok || !payload.access_token) {
        throw new GitHubApiError(payload.error_description || "GitHub 토큰 교환에 실패했습니다.");
    }
    return normaliseTokenResponse(payload);
};


const exchangeCode = (code, redirectUri, codeVerifier, env) => requestToken({
    client_id: env.GITHUB_CLIENT_ID,
    client_secret: env.GITHUB_CLIENT_SECRET,
    code,
    redirect_uri: redirectUri,
    code_verifier: codeVerifier,
}, env);


const refreshAccessToken = (refreshToken, env) => requestToken({
    client_id: env.GITHUB_CLIENT_ID,
    client_secret: env.GITHUB_CLIENT_SECRET,
    grant_type: "refresh_token",
    refresh_token: refreshToken,
}, env);


const githubUser = async (accessToken) => {
    const response = await fetch(`${GITHUB_API_URL}/user`, {
        headers: {
            "Accept": "application/vnd.github+json",
            "Authorization": `Bearer ${accessToken}`,
            "User-Agent": "algorithm-solutions-community",
            "X-GitHub-Api-Version": API_VERSION,
        },
    });
    if (!response.ok) throw new GitHubApiError("GitHub 사용자 정보를 확인하지 못했습니다.");
    const user = await response.json();
    if (!user.id || !user.login) throw new GitHubApiError("GitHub 사용자 정보가 올바르지 않습니다.");
    return {
        id: user.id,
        login: user.login,
        avatarUrl: user.avatar_url,
        profileUrl: user.html_url,
    };
};


const handleAuthCallback = async (request, env) => {
    const url = new URL(request.url);
    const stateToken = url.searchParams.get("state") || "";
    const stateKey = `oauth-state:${stateToken}`;
    const state = await env.COMMUNITY_KV.get(stateKey, "json");
    if (!state?.returnTo || !state?.callbackUrl || !state?.codeVerifier) {
        throw new HttpError(400, "로그인 요청이 만료되었거나 유효하지 않습니다.");
    }
    await env.COMMUNITY_KV.delete(stateKey);
    if (url.searchParams.get("error")) {
        return redirectWithError(state.returnTo, "GitHub 로그인이 취소되었습니다.");
    }
    const code = url.searchParams.get("code");
    if (!code) return redirectWithError(state.returnTo, "GitHub 로그인 코드가 없습니다.");

    try {
        const tokens = await exchangeCode(code, state.callbackUrl, state.codeVerifier, env);
        const user = await githubUser(tokens.accessToken);
        const sessionId = randomToken();
        await env.COMMUNITY_KV.put(
            `session:${sessionId}`,
            JSON.stringify({...tokens, user}),
            {expirationTtl: SESSION_TTL_SECONDS},
        );
        const returnUrl = new URL(state.returnTo);
        returnUrl.hash = new URLSearchParams({community_session: sessionId}).toString();
        return Response.redirect(returnUrl.toString(), 302);
    } catch (error) {
        return redirectWithError(state.returnTo, error.message || "GitHub 로그인에 실패했습니다.");
    }
};


const bearerToken = (request) => {
    const authorization = request.headers.get("Authorization") || "";
    const match = authorization.match(/^Bearer\s+(.+)$/i);
    if (!match) throw new HttpError(401, "GitHub 로그인이 필요합니다.");
    return match[1];
};


const requireSession = async (request, env) => {
    const sessionId = bearerToken(request);
    const sessionKey = `session:${sessionId}`;
    let session = await env.COMMUNITY_KV.get(sessionKey, "json");
    if (!session?.accessToken || !session?.user) {
        throw new HttpError(401, "로그인이 만료되었습니다. 다시 로그인해 주세요.");
    }
    if (session.accessTokenExpiresAt
        && session.accessTokenExpiresAt <= Date.now() + TOKEN_REFRESH_MARGIN_MS) {
        if (!session.refreshToken
            || (session.refreshTokenExpiresAt && session.refreshTokenExpiresAt <= Date.now())) {
            await env.COMMUNITY_KV.delete(sessionKey);
            throw new HttpError(401, "GitHub 로그인이 만료되었습니다. 다시 로그인해 주세요.");
        }
        try {
            const tokens = await refreshAccessToken(session.refreshToken, env);
            session = {...session, ...tokens};
            await env.COMMUNITY_KV.put(
                sessionKey,
                JSON.stringify(session),
                {expirationTtl: SESSION_TTL_SECONDS},
            );
        } catch {
            await env.COMMUNITY_KV.delete(sessionKey);
            throw new HttpError(401, "GitHub 로그인이 만료되었습니다. 다시 로그인해 주세요.");
        }
    }
    return {sessionId, ...session};
};


const githubGraphql = async (accessToken, query, variables) => {
    const response = await fetch(GITHUB_GRAPHQL_URL, {
        method: "POST",
        headers: {
            "Accept": "application/vnd.github+json",
            "Authorization": `Bearer ${accessToken}`,
            "Content-Type": "application/json",
            "User-Agent": "algorithm-solutions-community",
            "X-GitHub-Api-Version": API_VERSION,
        },
        body: JSON.stringify({query, variables}),
    });
    const payload = await response.json();
    if (!response.ok || payload.errors?.length) {
        const details = payload.errors || [];
        const message = details.map((item) => item.message).join("; ") || "GitHub API 요청에 실패했습니다.";
        throw new GitHubApiError(message, details);
    }
    return payload.data;
};


const repositoryMetadata = async (accessToken, env) => {
    const [owner, name] = String(env.GITHUB_REPOSITORY).split("/", 2);
    if (!owner || !name) throw new HttpError(503, "GITHUB_REPOSITORY 설정이 올바르지 않습니다.");
    const data = await githubGraphql(
        accessToken,
        `query RepositoryMetadata($owner: String!, $name: String!) {
          repository(owner: $owner, name: $name) {
            id
            discussionCategories(first: 25) {
              nodes { id name }
            }
          }
        }`,
        {owner, name},
    );
    const repository = data.repository;
    if (!repository) throw new GitHubApiError("평가를 저장할 GitHub 저장소를 찾지 못했습니다.");
    const categoryName = env.RATINGS_CATEGORY || "General";
    const category = repository.discussionCategories.nodes.find(
        (item) => item.name.toLowerCase() === categoryName.toLowerCase(),
    );
    if (!category) throw new GitHubApiError(`Discussion 카테고리를 찾지 못했습니다: ${categoryName}`);
    return {repositoryId: repository.id, categoryId: category.id};
};


const createDiscussion = async (accessToken, metadata, title, body) => {
    const data = await githubGraphql(
        accessToken,
        `mutation CreateRating($input: CreateDiscussionInput!) {
          createDiscussion(input: $input) {
            discussion { id number url }
          }
        }`,
        {
            input: {
                repositoryId: metadata.repositoryId,
                categoryId: metadata.categoryId,
                title,
                body,
            },
        },
    );
    return data.createDiscussion.discussion;
};


const updateDiscussion = async (accessToken, discussionId, title, body) => {
    const data = await githubGraphql(
        accessToken,
        `mutation UpdateRating($input: UpdateDiscussionInput!) {
          updateDiscussion(input: $input) {
            discussion { id number url }
          }
        }`,
        {input: {discussionId, title, body}},
    );
    return data.updateDiscussion.discussion;
};


const missingDiscussionError = (error) => error instanceof GitHubApiError && error.details.some(
    (item) => item.type === "NOT_FOUND" || /could not resolve|not found/i.test(item.message || ""),
);


const saveVote = async (session, vote, env) => {
    const mappingKey = `vote:${session.user.id}:${vote.problem}`;
    const existing = await env.COMMUNITY_KV.get(mappingKey, "json");
    const savedVote = {
        ...vote,
        recommendation: vote.recommendation ?? existing?.vote?.recommendation ?? null,
    };
    const title = `[평가] ${vote.problem}`;
    const body = buildDiscussionBody(savedVote, env.SITE_URL);
    let discussion;
    let created = false;

    if (existing?.discussionId) {
        try {
            discussion = await updateDiscussion(
                session.accessToken,
                existing.discussionId,
                title,
                body,
            );
        } catch (error) {
            if (!missingDiscussionError(error)) throw error;
            await env.COMMUNITY_KV.delete(mappingKey);
        }
    }
    if (!discussion) {
        const metadata = await repositoryMetadata(session.accessToken, env);
        discussion = await createDiscussion(session.accessToken, metadata, title, body);
        created = true;
    }
    await env.COMMUNITY_KV.put(
        mappingKey,
        JSON.stringify({
            discussionId: discussion.id,
            discussionNumber: discussion.number,
            discussionUrl: discussion.url,
            vote: {
                difficulty: savedVote.difficulty,
                difficultyName: savedVote.difficultyName,
                recommendation: savedVote.recommendation,
            },
        }),
    );
    return {discussion, created, vote: savedVote};
};


const handleVote = async (request, env) => {
    const session = await requireSession(request, env);
    let payload;
    try {
        payload = await request.json();
    } catch {
        throw new HttpError(400, "요청 JSON이 올바르지 않습니다.");
    }
    const vote = validateVote(payload);
    const rateKey = `rate:${session.sessionId}`;
    if (await env.COMMUNITY_KV.get(rateKey)) {
        throw new HttpError(429, "평가는 1분에 한 번 저장할 수 있습니다.");
    }
    await env.COMMUNITY_KV.put(rateKey, "1", {expirationTtl: VOTE_RATE_LIMIT_SECONDS});
    const result = await saveVote(session, vote, env);
    return jsonResponse(request, env, {
        ok: true,
        created: result.created,
        user: session.user,
        vote: {
            problem: result.vote.problem,
            difficulty: result.vote.difficulty,
            difficultyName: result.vote.difficultyName,
            recommendation: result.vote.recommendation,
        },
        discussionUrl: result.discussion.url,
        message: "평가가 GitHub Discussion에 저장되었습니다.",
    });
};


const route = async (request, env) => {
    const url = new URL(request.url);
    if (request.method === "OPTIONS") {
        return new Response(null, {status: 204, headers: corsHeaders(request, env)});
    }
    requireConfiguration(env);
    if (request.method === "GET" && url.pathname === "/health") {
        return jsonResponse(request, env, {
            ok: true,
            apiVersion: COMMUNITY_API_VERSION,
            repository: env.GITHUB_REPOSITORY,
        });
    }
    if (request.method === "GET" && url.pathname === "/auth/start") {
        return handleAuthStart(request, env);
    }
    if (request.method === "GET" && url.pathname === "/auth/callback") {
        return handleAuthCallback(request, env);
    }
    if (request.method === "GET" && url.pathname === "/session") {
        const session = await requireSession(request, env);
        return jsonResponse(request, env, {authenticated: true, user: session.user});
    }
    if (request.method === "GET" && url.pathname === "/vote") {
        const session = await requireSession(request, env);
        const problem = normaliseProblem(url.searchParams.get("problem"));
        const existing = await env.COMMUNITY_KV.get(`vote:${session.user.id}:${problem}`, "json");
        return jsonResponse(request, env, {vote: existing?.vote || null});
    }
    if (request.method === "POST" && url.pathname === "/logout") {
        const sessionId = bearerToken(request);
        await env.COMMUNITY_KV.delete(`session:${sessionId}`);
        return jsonResponse(request, env, {ok: true});
    }
    if (request.method === "POST" && url.pathname === "/vote") {
        return handleVote(request, env);
    }
    throw new HttpError(404, "API 경로를 찾을 수 없습니다.");
};


export default {
    async fetch(request, env) {
        try {
            return await route(request, env);
        } catch (error) {
            const status = error instanceof HttpError ? error.status : 500;
            const message = status === 500
                ? "커뮤니티 API 처리 중 오류가 발생했습니다."
                : error.message;
            if (status === 500) console.error(error);
            return jsonResponse(request, env, {ok: false, error: message}, status);
        }
    },
};

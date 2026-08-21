# 웹 평가 API

문제 페이지의 GitHub 로그인과 평가 저장을 담당하는 Cloudflare Worker입니다. 사용자는 문제 페이지 안에서 난이도를 제출하고 추천 여부는 선택적으로 남기며, Worker가 사용자의 GitHub App 토큰으로 GitHub Discussion을 생성하거나 갱신합니다. 같은 문제를 다시 평가하면 기존 값을 불러와 수정할 수 있습니다. OAuth secret과 GitHub 토큰은 정적 GitHub Pages에 노출되지 않습니다.

Cloudflare의 [Workers Free 요금제](https://developers.cloudflare.com/workers/platform/pricing/)에는 Worker와 제한된 Workers KV 사용량이 포함됩니다. 소규모 커뮤니티는 무료 한도에서 시작할 수 있으며, 운영 전에는 최신 요청·KV 한도를 확인하세요.

## 최초 배포

### 1. 저장소 기능 준비

1. GitHub 저장소의 `Settings > General > Features`에서 Discussions를 활성화합니다.
2. `Announcements`와 `General` Discussion 카테고리를 유지합니다.
3. [giscus GitHub App](https://github.com/apps/giscus)을 이 저장소에 설치합니다.

댓글 입력창을 활성화하려면 위 준비 후 `Sync GitHub Discussions` workflow를 수동으로 한 번 실행합니다. 성공한 workflow가 `community-data/discussions.json`에 저장소와 `Announcements` 카테고리 ID를 기록하고 push하면, 동기화 완료 이벤트를 받은 `GitHub Pages` workflow가 다시 실행됩니다. 배포 결과에서 `Discussion 연동 준비 중` 안내 대신 giscus 댓글 입력창이 표시되는지 확인합니다.

### 2. Worker URL 만들기

[Cloudflare 계정](https://dash.cloudflare.com/)을 준비한 뒤 저장소 루트에서 실행합니다.

```bash
cd community-worker
npm install
npx wrangler login
npm run deploy
```

첫 배포가 끝나면 출력된 `https://...workers.dev` 주소를 기록합니다. KV namespace는 `wrangler.jsonc`의 binding을 기준으로 자동 생성됩니다. 이 시점에는 아직 GitHub secret이 없으므로 API가 `503`을 반환하는 것이 정상입니다.

### 3. GitHub App 만들기

GitHub의 `Settings > Developer settings > GitHub Apps > New GitHub App`에서 앱을 만듭니다.

- Homepage URL: `https://tony9402.github.io/algorithm-solutions/`
- Callback URL: `https://<Worker 주소>/auth/callback`
- Webhook: 비활성화
- Repository permissions: `Discussions`를 `Read and write`로 설정
- 설치 범위: 이 계정만 허용하고 `tony9402/algorithm-solutions` 저장소에만 설치

일반 OAuth App이 아니라 GitHub App을 쓰는 이유는 사용자에게 `public_repo`처럼 모든 공개 저장소에 적용되는 넓은 scope를 요청하지 않기 위해서입니다. GitHub App user access token은 사용자의 권한과 앱이 설치된 저장소 권한의 교집합으로 제한됩니다. 토큰 만료 기능은 켜 두어도 Worker가 refresh token으로 갱신합니다.

앱 생성 뒤 Client ID와 새 Client secret을 Worker secret으로 등록하고 다시 배포합니다.

```bash
cd community-worker
npx wrangler secret put GITHUB_CLIENT_ID
npx wrangler secret put GITHUB_CLIENT_SECRET
npm run deploy
```

이후 `community-worker/` 코드가 바뀔 때도 Pages 배포와 별개로 `npm run deploy`를 다시 실행해야 합니다. Pages만 갱신하면 새 프런트엔드가 아직 배포되지 않은 API 경로를 호출할 수 있습니다. 배포 확인은 다음처럼 하며, 현재 프런트엔드는 `apiVersion` 2 이상이 필요합니다.

```bash
curl https://<Worker 주소>/health
```

응답에 `"apiVersion":2`가 없거나 로그인 뒤 `API 경로를 찾을 수 없습니다.`가 표시되면 Worker가 이전 버전이므로 다시 배포합니다. Wrangler secret은 Worker를 다시 배포해도 그대로 유지됩니다.

### 4. Pages에 API 주소 연결

GitHub 저장소의 `Settings > Secrets and variables > Actions > Variables`에 다음 repository variable을 추가합니다.

- 이름: `COMMUNITY_VOTE_API_URL`
- 값: `https://<Worker 주소>` (끝의 `/` 제외)

그다음 `GitHub Pages` workflow를 수동 실행합니다. 문제 페이지에 GitHub 로그인 버튼이 활성화됩니다. 마지막으로 `Sync GitHub Discussions` workflow를 한 번 실행하면 Discussion 카테고리 ID가 정적 데이터에 기록되고 giscus 댓글 입력창도 활성화됩니다.

## 로컬 미리보기

GitHub App에 `http://127.0.0.1:8787/auth/callback`을 추가 Callback URL로 등록합니다. `community-worker/.dev.vars.example`을 `.dev.vars`로 복사한 뒤 실제 Client ID와 secret을 입력합니다. `.dev.vars`는 git에서 제외됩니다.

터미널 1에서 Worker를 실행합니다.

```bash
cd community-worker
npm install
npm run dev
```

터미널 2에서 로컬 API 주소를 넣어 정적 사이트를 빌드하고 제공합니다.

```bash
COMMUNITY_VOTE_API_URL=http://127.0.0.1:8787 \
  .venv/bin/python pages/build.py --base-path ""
.venv/bin/python -m http.server 8765 -d _site
```

이제 `http://127.0.0.1:8765/problems/baekjoon/1000/`에서 로그인과 평가 폼을 확인할 수 있습니다. 실제 로그인 없이 UI만 확인하려면 Worker를 실행하지 않고 `COMMUNITY_VOTE_API_URL=http://127.0.0.1:8787`로 빌드해도 됩니다. 이 경우 버튼과 폼은 보이지만 로그인 요청은 실패합니다.

## 환경 설정

공개 설정은 `wrangler.jsonc`에서 관리합니다.

- `GITHUB_REPOSITORY`: 평가 Discussion을 저장할 `owner/repository`
- `RATINGS_CATEGORY`: 평가를 저장할 Discussion 카테고리 이름
- `ALLOWED_ORIGINS`: CORS와 OAuth 복귀를 허용할 사이트 origin 목록
- `SITE_URL`: Discussion 본문에 기록할 운영 사이트 주소
- `COMMUNITY_KV`: OAuth state, 세션, 사용자별 Discussion ID를 보관하는 KV binding

`GITHUB_CLIENT_ID`와 `GITHUB_CLIENT_SECRET`은 반드시 Wrangler secret으로만 저장합니다.

## 동작 방식

1. 로그인 버튼이 Worker의 `/auth/start`를 엽니다.
2. Worker는 `state`와 PKCE를 적용한 GitHub App web application flow를 시작합니다.
3. 로그인 성공 뒤 Worker는 GitHub 토큰을 KV에 보관하고, 문제 페이지 URL fragment로 임의 세션 ID만 돌려보냅니다.
4. 브라우저는 세션 ID를 `sessionStorage`에 저장하고 `/vote`에 난이도와 추천 여부를 제출합니다.
5. Worker는 사용자·문제별 기존 Discussion이 있으면 수정하고 없으면 생성합니다.
6. 매일 GitHub Actions가 Discussion을 집계해 `community-data/discussions.json`을 갱신합니다.

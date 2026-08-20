# GitHub Discussion 커뮤니티 데이터

`discussions.json`은 GitHub Discussions를 원본으로 생성되는 정적 스냅샷입니다. 이 파일을 저장소에 커밋하므로 사이트 밖으로 이동하거나 저장소를 clone해도 문제별 최신 평가를 확인할 수 있습니다.

## 데이터 흐름

1. 문제 페이지의 댓글은 giscus를 통해 `Announcements` 카테고리의 문제별 Discussion에 저장됩니다.
2. 사용자는 문제 페이지 안에서 GitHub로 로그인하고 난이도와 추천 여부를 제출합니다.
3. Cloudflare Worker가 로그인한 사용자의 권한으로 `General` 카테고리에 평가 Discussion을 생성하거나 기존 평가를 갱신합니다. 사용자는 Discussion 화면을 직접 열지 않습니다.
4. `.github/workflows/sync_discussions.yml`이 매일 00:17 KST에 두 카테고리를 읽습니다.
5. 같은 GitHub 사용자가 같은 문제에 여러 평가를 남기면 `updatedAt`이 가장 최신인 1건만 반영합니다.
6. 집계가 바뀌면 이 파일을 커밋하고 Pages 워크플로가 최신 스냅샷으로 사이트를 다시 배포합니다.

## 최초 저장소 설정

코드를 병합한 뒤 저장소 관리자가 다음 설정을 한 번 수행해야 합니다.

1. 저장소 `Settings > General > Features`에서 Discussions를 활성화합니다.
2. 기본 `Announcements`와 `General` 카테고리를 유지합니다. 이름을 바꾸면 Worker와 동기화 워크플로의 카테고리 설정도 함께 변경해야 합니다.
3. [giscus GitHub App](https://github.com/apps/giscus)을 이 저장소에 설치합니다.
4. [`community-worker/README.md`](../community-worker/README.md)에 따라 평가 API를 배포하고 Pages의 `COMMUNITY_VOTE_API_URL` 변수를 설정합니다.
5. Actions의 `Sync GitHub Discussions`를 수동으로 한 번 실행합니다. 카테고리 ID가 `discussions.json`에 기록되면 댓글 입력창이 활성화됩니다.
6. 저장소의 Actions 설정에서 워크플로가 `contents: write` 권한을 사용할 수 있어야 합니다.

GitHub Pages에는 secret을 넣지 않습니다. 댓글 로그인은 giscus가 처리하고, 평가 로그인 토큰은 Cloudflare Worker의 KV에만 저장합니다. 브라우저에는 임의의 세션 ID만 `sessionStorage`에 보관됩니다.

## 로컬 동기화

Discussion 읽기 권한이 있는 토큰을 `GH_TOKEN`에 설정한 후 다음 명령으로 동일한 스냅샷을 만들 수 있습니다.

```bash
python scripts/sync_discussion_data.py \
  --repository tony9402/algorithm-solutions \
  --comments-category Announcements \
  --ratings-category General
```

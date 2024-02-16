// Authored by : tony9402
// Co-authored by : -
// Link : http://boj.kr/8c1a3a3c7634449398e61eb168a9e5c1
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M; cin >> N >> M;
    vector<vector<pair<int, int>>> G(N + 1);
    for(int i = 0; i < M; ++i) {
        int u, v, w; cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    int S, T; cin >> S >> T;

    priority_queue<pair<int, int>> pq;
    const int INF = 0x3f3f3f3f;
    vector<int> dist(N + 1, INF);
    dist[S] = 0;
    pq.emplace(0, S);
    while(!pq.empty()) {
        auto [d, cur] = pq.top(); pq.pop();
        if(dist[cur] != -d) continue;
        for(auto [nxt, w]: G[cur]) {
            if(dist[nxt] > dist[cur] + w) {
                dist[nxt] = dist[cur] + w;
                pq.emplace(-dist[nxt], nxt);
            }
        }
    }
    cout << dist[T];

    return 0;
}

/* Solution Description

풀이과정  

```
MST 문제처럼 보이지만 조금 다른건 S랑 T가 연결될때까지 한다.  
그러면 S에서 T로 가는 길에 존재하는 모든 가중치의 합 중 최솟값을 구하면 되는거 아닌가?
근데 연결되어 있다는 보장은? 연결 그래프 보장이니깐 되어 있다.
그럼 그냥 다익 돌리면 되는데?
```
*/
// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/submissions/1583339997
using ll = long long;
class Solution {
public:
    int countPaths(int N, vector<vector<int>>& roads) {
        vector<vector<pair<int, ll>>> G(N);
        for(int i = 0; i < (int)roads.size(); ++i) {
            int u = roads[i][0], v = roads[i][1];
            ll w = roads[i][2];
            G[u].emplace_back(v, w);
            G[v].emplace_back(u, w);
        }
        const ll INF = LLONG_MAX / 2;
        priority_queue<pair<ll, int>> pq;
        vector<ll> dist(N, INF), DP(N);
        dist[0] = 0; DP[0] = 1; pq.emplace(0, 0);
        const ll MOD = 1e9 + 7;
        while(!pq.empty()) {
            auto [d, cur] = pq.top(); pq.pop();
            if(dist[cur] != -d) continue;
            for(auto [nxt, w]: G[cur]) {
                if(dist[nxt] > dist[cur] + w) {
                    dist[nxt] = dist[cur] + w;
                    DP[nxt] = DP[cur];
                    pq.emplace(-dist[nxt], nxt);
                }
                else if(dist[nxt] == dist[cur] + w) DP[nxt] = (DP[nxt] + DP[cur]) % MOD;
            }
        }
        return DP[N - 1];
    }
};

/* Solution Description
*/

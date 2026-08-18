// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/cheapest-flights-within-k-stops/submissions/1183606527
class Solution {
public:
    int findCheapestPrice(int N, vector<vector<int>>& flights, int src, int dst, int K) {
        vector<vector<pair<int, int>>> G(N);
        for(int i = 0; i < flights.size(); ++i) {
            int u = flights[i][0], v = flights[i][1], w = flights[i][2];
            G[u].emplace_back(v, w);
        }
        const int INF = 0x3f3f3f3f;
        vector<vector<int>> DP(K + 2, vector<int>(N, INF));
        vector<priority_queue<pair<int, int>>> pqs(K + 1);
        pqs[0].emplace(0, src); DP[0][src] = 0;
        int mn = INF;
        for(int k = 0; k <= K; ++k) {
            while(!pqs[k].empty()) {
                auto [d, cur] = pqs[k].top(); pqs[k].pop();
                if(cur == dst) mn = min(mn, DP[k][cur]);
                if(DP[k][cur] != -d) continue;
                for(const auto &[nxt, w]: G[cur]) {
                    if(DP[k + 1][nxt] > -d + w) {
                        DP[k + 1][nxt] = -d + w;
                        if(k+1<=K) pqs[k+1].emplace(d - w, nxt);
                    }
                }
            }
        }
        mn = min(mn, DP[K + 1][dst]);
        if(mn == INF) mn = -1;
        return mn;
    }
};

/* Solution Description
*/

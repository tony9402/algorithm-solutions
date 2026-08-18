// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/most-profitable-path-in-a-tree/submissions/1553834833
class Solution {
public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
        int N = (int)amount.size();
        vector<vector<int>> G(N);
        for(int i = 0; i < (int)edges.size(); ++i) {
            int u = edges[i][0], v = edges[i][1];
            G[u].emplace_back(v); G[v].emplace_back(u);
        }
        vector<int> dist(N);
        function<int(int, int, int)> dfs = [&](int cur, int prev, int dep) -> int {
            dist[cur] = cur == bob ? 0 : N;
            int mx = INT_MIN, mx2 = 0;
            for(int nxt: G[cur]) {
                if(nxt == prev) continue;
                mx = max(mx, dfs(nxt, cur, dep + 1));
                dist[cur] = min(dist[cur], dist[nxt] + 1);
            }
            if(dist[cur] > dep) mx2 += amount[cur];
            else if(dist[cur] == dep) mx2 += amount[cur] / 2;
            return mx == INT_MIN ? mx2 : mx + mx2;
        };
        return dfs(0, 0, 0);
    }
};

/* Solution Description
*/

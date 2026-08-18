// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/submissions/1579640413
class Solution {
public:
    vector<int> minimumCost(int N, vector<vector<int>>& edges, vector<vector<int>>& query) {
        vector<int> uf(N + 1, -1);
        function<int(int)> find = [&](int x) -> int {
            return uf[x] < 0 ? x : uf[x] = find(uf[x]);
        };
        function<bool(int, int)> merge = [&](int u, int v) -> bool {
            u = find(u); v = find(v);
            if(u == v) return false;
            uf[v] = u;
            return true;
        };
        for(const auto &e: edges) {
            int u = e[0], v = e[1], w = e[2];
            merge(u, v);
        }
        vector<int> cost(N + 1, -1);
        for(const auto &e: edges) {
            int u = e[0], v = e[1], w = e[2];
            u = find(u);
            if(cost[u] < 0) cost[u] = w;
            else cost[u] &= w;
        }
        vector<int> answer;
        for(const auto &q: query) {
            int u = q[0], v = q[1];
            if(find(u) != find(v)) answer.push_back(-1);
            else answer.push_back(cost[find(u)]);
        }
        return answer;
    }
};

/* Solution Description
*/

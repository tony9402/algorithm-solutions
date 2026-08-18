// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/redundant-connection/submissions/1523836487
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int N = (int)edges.size() + 1;
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
        int answer = 0;
        for(int i = 0; i + 1 < N; ++i) {
            int u = edges[i][0], v = edges[i][1];
            if(!merge(u, v)) answer = i;
        }
        return edges[answer];
    }
};

/* Solution Description
*/

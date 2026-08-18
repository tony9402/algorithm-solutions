// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/making-a-large-island/submissions/1526033314
const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};
class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int N = (int)grid.size(), M = (int)grid[0].size();
        vector<int> uf(N * M, -1), siz(N * M);
        function<int(int)> find = [&](int x) -> int {
            return uf[x] < 0 ? x : uf[x] = find(uf[x]);
        };
        function<bool(int, int)> merge = [&](int u, int v) -> bool {
            u = find(u); v = find(v);
            if(u == v) return false;
            uf[v] = u;
            siz[u] += siz[v];
            siz[v] = 0;
            return true;
        };
        for(int i = 0; i < N; ++i) for(int j = 0; j < M; ++j) siz[i * M + j] = grid[i][j];
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                if(grid[i][j] == 0) continue;
                for(int k = 0; k < 4; ++k) {
                    int qy = i + dy[k], qx = j + dx[k];
                    if(0 > qy || qy >= N || 0 > qx || qx >= M) continue;
                    if(grid[qy][qx]) merge(i * M + j, qy * M + qx);
                }
            }
        }
        int ans = 0, mx = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                if(grid[i][j]) mx = max(mx, siz[find(i * M + j)]);
                else {
                    set<int> st;
                    int cur_size = 1;
                    for(int k = 0; k < 4; ++k) {
                        int qy = i + dy[k], qx = j + dx[k];
                        if(0 > qy || qy >= N || 0 > qx || qx >= M || !grid[qy][qx]) continue;
                        int x = find(qy * M + qx);
                        if(st.count(x)) continue;
                        st.insert(x);
                        cur_size += siz[x];
                    }
                    ans = max(ans, cur_size);
                }
            }
        }
        ans = max(ans, mx);
        return ans;
    }
};

/* Solution Description
*/

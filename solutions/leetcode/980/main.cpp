// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/unique-paths-iii/submissions/762154777
class Solution {
    static constexpr int dy[] = {0,0,-1,1};
    static constexpr int dx[] = {-1,1,0,0};
public:
    int N, M;
    vector<vector<vector<int>>> DP;
    vector<vector<int>> G;
    inline int getpos(int y, int x) { return y * M + x; }
    int dfs(int y, int x, int bits) {
        int &ret = DP[y][x][bits];
        if(ret != -1) return ret;
        ret = 0;
        for(int k = 0; k < 4; ++k) {
            int qy = y + dy[k], qx = x + dx[k];
            if(0 > qy || qy >= N || 0 > qx || qx >= M || G[qy][qx] == -1) continue;
            int b = 1 << getpos(qy, qx);
            if(bits & b) continue;
            ret += dfs(qy, qx, bits | b);
        }
        return ret;
    }
    int uniquePathsIII(vector<vector<int>>& grid) {
        G = grid;
        N = (int)grid.size(), M = (int)grid[0].size();
        DP = vector<vector<vector<int>>>(N, vector<vector<int>>(M, vector<int>(1 << (N*M), -1)));
        int sy, sx, ey, ex, cnt = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                if(grid[i][j] == 1) sy = i, sx = j;
                if(grid[i][j] == 2) ey = i, ex = j;
                if(grid[i][j] != -1) cnt ++;
            }
        }
        DP[ey][ex][(1 << cnt) - 1] = 1;
        return dfs(sy, sx, 1 << getpos(sy, sx));
    }
};

/* Solution Description
*/

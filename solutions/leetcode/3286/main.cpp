// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-a-safe-walk-through-a-grid/submissions/2053290844
class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int N = (int)grid.size();
        int M = (int)grid[0].size();
        const int dy[] = {-1,1,0,0};
        const int dx[] = {0,0,-1,1};
        vector<vector<vector<int>>> used(health + 1, vector<vector<int>>(N, vector<int>(M)));
        queue<tuple<int, int, int>> Q;
        Q.emplace(0, 0, health - grid[0][0]);
        used[health - grid[0][0]][0][0] = 1;
        while(!Q.empty()) {
            auto [y, x, h] = Q.front(); Q.pop();
            for(int k = 0; k < 4; ++k) {
                int qy = y + dy[k];
                int qx = x + dx[k];
                if(0 > qy || qy >= N || 0 > qx || qx >= M) continue;
                if(h - grid[qy][qx] <= 0) continue;
                if(used[h - grid[qy][qx]][qy][qx]) continue;
                used[h - grid[qy][qx]][qy][qx] = 1;
                Q.emplace(qy, qx, h - grid[qy][qx]);
            }
        }
        int ans = 0;
        for(int i = 1; i <= health; ++i) ans |= used[i][N - 1][M - 1];
        return ans;
    }
};

/* Solution Description
*/

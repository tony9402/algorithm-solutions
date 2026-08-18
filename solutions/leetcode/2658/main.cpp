// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/submissions/1524245071
const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};

class Solution {
public:
    int findMaxFish(vector<vector<int>>& grid) {
        int N = (int)grid.size(), M = (int)grid[0].size();
        queue<pair<int, int>> Q;
        int answer = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                if(grid[i][j] == 0) continue;
                int size = grid[i][j];
                queue<pair<int, int>> Q({{i, j}});
                grid[i][j] = 0;
                while(!Q.empty()) {
                    auto [y, x] = Q.front(); Q.pop();
                    for(int k = 0; k < 4; ++k) {
                        int ny = y + dy[k], nx = x + dx[k];
                        if(0 > ny || ny >= N || 0 > nx || nx >= M) continue;
                        if(grid[ny][nx] == 0) continue;
                        size += grid[ny][nx];
                        grid[ny][nx] = 0;
                        Q.emplace(ny, nx);
                    }
                }
                answer = max(answer, size);
            }
        }
        return answer;
    }
};

/* Solution Description
*/

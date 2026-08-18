// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/submissions/1512454688
const int dy[] = {0,0,1,-1};
const int dx[] = {1,-1,0,0};

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int N = (int)grid.size();
        int M = (int)grid[0].size();
        deque<tuple<int, int, int>> dq;
        const int INF = 0x3f3f3f3f;
        vector<vector<int>> D(N, vector<int>(M, INF));
        dq.emplace_back(0, 0, 0); D[0][0] = 0;
        while(!dq.empty()) {
            auto [d, y, x] = dq.front(); dq.pop_front();
            // if(D[y][x] != d) continue;
            for(int k = 1; k <= 4; ++k) {
                int qy = y + dy[k - 1], qx = x + dx[k - 1];
                if(0 > qy || qy >= N || 0 > qx || qx >= M) continue;
                int nd = D[y][x] + (grid[y][x] != k);
                if(D[qy][qx] > nd) {
                    D[qy][qx] = nd;
                    //if(nd == D[y][x]) dq.emplace_front(nd, qy, qx);
                    // else
                    dq.emplace_back(nd, qy, qx);
                }
            }
        }
        return D[N - 1][M - 1];
    }
};

/* Solution Description
*/

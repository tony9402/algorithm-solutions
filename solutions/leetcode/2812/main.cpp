// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-the-safest-path-in-a-grid/submissions/2051951370
class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int N = (int)grid.size();
        vector<vector<int>> dist(N, vector<int>(N, -1));
        const int dy[] = {-1,1,0,0};
        const int dx[] = {0,0,-1,1};
        {
            queue<pair<int, int>> Q;
            for(int i = 0; i < N; ++i) {
                for(int j = 0; j < N; ++j) {
                    if(grid[i][j] == 1) {
                        Q.emplace(i, j);
                        dist[i][j] = 0;
                    }
                }
            }
            while(!Q.empty()) {
                auto [y, x] = Q.front(); Q.pop();
                for(int k = 0; k < 4; ++k) {
                    int qy = y + dy[k];
                    int qx = x + dx[k];
                    if(0 > qy || qy >= N || 0 > qx || qx >= N) continue;
                    if(dist[qy][qx] != -1) continue;
                    dist[qy][qx] = dist[y][x] + 1;
                    Q.emplace(qy, qx);
                }
            }
        }

        function<bool(int)> chk = [&](int mid) -> bool {
            vector<vector<int>> chk(N, vector<int>(N));
            queue<pair<int, int>> Q;
            if(dist[0][0] >= mid) {
                Q.emplace(0, 0);
                chk[0][0] = 1;
            }
            while(!Q.empty()) {
                auto [y,x] = Q.front(); Q.pop();
                for(int k = 0; k < 4; ++k) {
                    int qy = y + dy[k];
                    int qx = x + dx[k];
                    if(0 > qy || qy >= N || 0 > qx || qx >= N) continue;
                    if(chk[qy][qx] || dist[qy][qx] < mid) continue;
                    chk[qy][qx] = 1;
                    Q.emplace(qy, qx);
                }
            }
            return chk[N - 1][N - 1];
        };

        int lo = 0, hi = 4 * N;
        while(lo <= hi) {
            int mid = (lo + hi) / 2;
            if(chk(mid)) lo = mid + 1;
            else hi = mid - 1;
        }
        return hi;
    }
};

/* Solution Description
*/

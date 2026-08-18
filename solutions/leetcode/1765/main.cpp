// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/map-of-highest-peak/submissions/1524251097
const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};
class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        queue<pair<int, int>> Q;
        int N = (int)isWater.size(), M = (int)isWater[0].size();
        vector<vector<int>> used(N, vector<int>(M));
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                if(isWater[i][j] == 1) {
                    Q.emplace(i, j);
                    used[i][j] = 1;
                    isWater[i][j] = 0;
                }
            }
        }
        while(!Q.empty()) {
            auto [y, x] = Q.front(); Q.pop();
            for(int k = 0; k < 4; ++k) {
                int qy = y + dy[k], qx = x + dx[k];
                if(0 > qy || qy >= N || 0 > qx || qx >= M || used[qy][qx]) continue;
                used[qy][qx] = 1;
                isWater[qy][qx] = isWater[y][x] + 1;
                Q.emplace(qy, qx);
            }
        }
        return isWater;
    }
};

/* Solution Description
*/

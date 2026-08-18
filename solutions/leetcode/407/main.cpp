// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/trapping-rain-water-ii/submissions/1513408976
const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int N = (int)heightMap.size();
        int M = (int)heightMap[0].size();
        vector<vector<pair<int, int>>> Q(20001);
        vector<vector<int>> used(N, vector<int>(M));
        for(int i = 0; i < N; ++i) {
            Q[heightMap[i][0]].emplace_back(i, 0);
            Q[heightMap[i][M - 1]].emplace_back(i, M - 1);
            used[i][0] = used[i][M - 1] = 1;
        }
        for(int j = 0; j < M; ++j) {
            Q[heightMap[0][j]].emplace_back(0, j);
            Q[heightMap[N - 1][j]].emplace_back(N - 1, j);
            used[0][j] = used[N - 1][j] = 1;
        }
        int answer = 0;
        for(int h = 0; h <= 20000; ++h) {
            while(!Q[h].empty()) {
                auto [y, x] = Q[h].back(); Q[h].pop_back();
                for(int k = 0; k < 4; ++k) {
                    int qy = y + dy[k], qx = x + dx[k];
                    if(0 > qy || qy >= N || 0 > qx || qx >= M || used[qy][qx]) continue;
                    used[qy][qx] = 1;
                    answer += max(0, h - heightMap[qy][qx]);
                    Q[max(h, heightMap[qy][qx])].emplace_back(qy, qx);
                }
            }
        }
        return answer;
    }
};

/* Solution Description
*/

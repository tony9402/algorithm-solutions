// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/submissions/1586391985
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<vector<int>> V(x);
        int N = (int)grid.size();
        int M = (int)grid[0].size();
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                int y = grid[i][j];
                V[y % x].push_back(y);
            }
        }
        int ans = -1;
        for(int i = 0; i < x; ++i) {
            if(V[i].size() > 0 && V[i].size() != N * M) return -1;
            if(V[i].empty()) continue;
            ans = INT_MAX;
            sort(V[i].begin(), V[i].end());
            vector<long long> P(N * M + 1);
            for(int j = 0; j < N * M; ++j) P[j + 1] = P[j] + V[i][j];
            for(int j = 1; j <= N * M; ++j) {
                long long l = 1LL * V[i][j - 1] * (j - 1) - P[j - 1];
                long long r = P[N * M] - P[j] - 1LL * V[i][j - 1] * (N * M - j);
                ans = min<long long>(ans, l / x + r / x);
            }
            break;
        }
        return ans;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/submissions/823617395
class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int N = (int)jobDifficulty.size();
        if(N < d) return -1;
        const int INF = INT_MAX / 2;
        vector<vector<int>> DP(N + 1, vector<int>(d + 1, INF));
        DP[0][0] = 0;
        for(int j = 1; j <= d; ++j) {
            for(int i = 1; i <= N; ++i) {
                for(int k = i - 1, mx = 0; k >= j - 1; --k) {
                    mx = max(mx, jobDifficulty[k]);
                    DP[i][j] = min(DP[i][j], DP[k][j - 1] + mx);
                }
            }
        }
        return DP[N][d];
    }
};

/* Solution Description
*/

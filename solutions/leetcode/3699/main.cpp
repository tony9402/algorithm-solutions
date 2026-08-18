// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/number-of-zigzag-arrays-i/submissions/2043092451
class Solution {
public:
    int zigZagArrays(int N, int l, int r) {
        const int MOD = 1e9 + 7;
        vector<vector<vector<int>>> DP(2, vector<vector<int>>(r + 2, vector<int>(2)));
        int toggle = 1;
        for(int i = l; i <= r; ++i) {
            DP[toggle][i][0] = DP[toggle][i][1] = 1;
        }
        for(int i = 2; i <= N; ++i) {
            for(int j = l; j <= r; ++j) DP[toggle ^ 1][j][0] = DP[toggle ^ 1][j][1] = 0;
            for(int j = l; j <= r; ++j) {
                DP[toggle ^ 1][j][0] = (DP[toggle ^ 1][j][0] + DP[toggle][j - 1][1]) % MOD;
                DP[toggle ^ 1][j][1] = (DP[toggle ^ 1][j][1] + DP[toggle][j + 1][0]) % MOD;
            }
            toggle ^= 1;
            for(int j = l; j <= r; ++j) {
                DP[toggle][j][0] = (DP[toggle][j][0] + DP[toggle][j - 1][0]) % MOD;
            }
            for(int j = r; j >= l; --j) {
                DP[toggle][j][1] = (DP[toggle][j][1] + DP[toggle][j + 1][1]) % MOD;
            }
        }
        int ans = 0;
        for(int i = l; i <= r; ++i) ans = ((ans + DP[toggle][i][0]) % MOD + DP[toggle][i][1]) % MOD;
        return ans;
    }
};

/* Solution Description
*/

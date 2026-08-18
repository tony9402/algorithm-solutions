// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/unique-paths/submissions/1187352514
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> DP(m + 1, vector<int>(n + 1));
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(i == 1 || j == 1) DP[i][j] = 1;
                else  DP[i][j] = DP[i - 1][j] + DP[i][j - 1];
            }
        }
        return DP[m][n];
    }
};

/* Solution Description
*/

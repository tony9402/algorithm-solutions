// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximal-square/submissions/1436065941
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int N = (int)matrix.size(), M = (int)matrix[0].size();
        vector<vector<int>> DP(N + 1, vector<int>(M + 1));
        int ans = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                if(matrix[i][j] == '1') {
                    DP[i + 1][j + 1] = 1 + min({DP[i][j + 1], DP[i + 1][j], DP[i][j]});
                }
                ans = max(ans, DP[i + 1][j + 1]);
            }
        }
        return ans * ans;
    }
};

/* Solution Description
*/

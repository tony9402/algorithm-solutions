// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/shortest-common-supersequence/submissions/1559247186
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int N = (int)str1.size(), M = (int)str2.size();
        vector<vector<int>> DP(N + 1, vector<int>(M + 1));
        for(int i = 1; i <= N; ++i) {
            for(int j = 1; j <= M; ++j) {
                if(str1[i - 1] == str2[j - 1]) DP[i][j] = DP[i - 1][j - 1] + 1;
                else  DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
            }
        }
        int y = N, x = M;
        string ans = "";
        while(y > 0 && x > 0) {
            if(str1[y - 1] == str2[x - 1])  ans += str1[-- y], --x;
            else if(DP[y - 1][x] > DP[y][x - 1]) ans += str1[--y];
            else ans += str2[-- x];
        }
        while(y > 0) ans += str1[-- y];
        while(x > 0) ans += str2[-- x];
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

/* Solution Description
*/

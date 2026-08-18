// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/unique-length-3-palindromic-subsequences/submissions/1497110876
class Solution {
public:
    int countPalindromicSubsequence(string s) {
        int N = (int)s.size();
        vector<vector<int>> chk(26, vector<int>(26));
        vector<vector<int>> L(N + 2, vector<int>(26));
        vector<vector<int>> R(N + 2, vector<int>(26));
        for(int i = N; i >= 1; --i) {
            int idx = s[i - 1] - 'a';
            for(int j = 0; j < 26; ++j) R[i][j] += R[i + 1][j];
            ++ R[i][idx];
        }
        for(int i = 1; i <= N; ++i) {
            int idx = s[i - 1] - 'a';
            for(int j = 0; j < 26; ++j) {
                if(L[i - 1][j] && R[i + 1][j]) chk[idx][j] = 1;
            }
            for(int j = 0; j < 26; ++j) L[i][j] += L[i - 1][j];
            ++ L[i][idx];
        }
        int answer = 0;
        for(int i = 0; i < 26; ++i) for(int j = 0; j < 26; ++j) answer += chk[i][j];
        return answer;
    }
};

/* Solution Description
*/

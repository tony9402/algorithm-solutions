// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-first-palindromic-string-in-the-array/submissions/1173763525
class Solution {
public:
    string firstPalindrome(vector<string>& words) {
        for(string &S: words) {
            int N = S.size();
            bool flag = true;
            for(int i = 0; flag && i * 2 <= N; ++i) {
                if(S[i] != S[N - 1 - i]) flag = false;
            }
            if(flag) return S;
        }
        return "";
    }
};

/* Solution Description
*/

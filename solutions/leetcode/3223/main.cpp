// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-length-of-string-after-operations/submissions/1506953606
class Solution {
public:
    int minimumLength(string s) {
        vector<int> cnt(26);
        for(const char &ch: s)  ++ cnt[ch - 'a'];
        int answer = 0;
        for(int i = 0; i < 26; ++i) {
            if(cnt[i] <= 2) answer += cnt[i];
            else answer += cnt[i] % 2 ? 1 : 2;
        }
        return answer;
    }
};

/* Solution Description
*/

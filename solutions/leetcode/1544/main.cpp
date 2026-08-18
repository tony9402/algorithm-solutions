// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/make-the-string-great/submissions/1223744938
class Solution {
public:
    string makeGood(string s) {
        int i = 1, j = 0;
        for(; i < (int)s.size(); ++i) {
            if(j >= 0 && (s[j] ^ s[i]) == 32) --j;
            else s[++j] = s[i];
        }
        return s.substr(0, j + 1);
    }
};

/* Solution Description
*/

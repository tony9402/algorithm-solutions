// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/valid-parenthesis-string/submissions/1226673258
class Solution {
public:
    bool checkValidString(string s) {
        int l = 0, r = 0;
        for(char ch: s) {
            l += (ch == '(' ? 1 : -1);
            r += (ch != ')' ? 1 : -1);
            if(r < 0) return false;
            l = max(l, 0);
        }
        return l == 0;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/submissions/1506022118
class Solution {
public:
    bool canBeValid(string s, string locked) {
        int N = (int)s.size();
        if(N & 1) return false;
        int l = 0, r = 0;
        for(int i = 0; i < N; ++i) {
            if(s[i] == '(' || locked[i] == '0') ++ r;
            else -- r;
            if(s[i] == ')' || locked[i] == '0') -- l;
            else ++ l;
            if(r < 0) return false;
            l = max(l, 0);
        }
        return l == 0;
    }
};

/* Solution Description
*/

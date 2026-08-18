// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/submissions/1222934149
class Solution {
public:
    int maxDepth(string s) {
        int ans = 0, top = 0;
        for(const char &ch: s) {
            if(ch == '(') ans = max(ans, ++top);
            else if(ch == ')') -- top;
        }
        return ans;
    }
};

/* Solution Description
*/

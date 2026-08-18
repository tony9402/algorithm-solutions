// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-length-of-string-after-deleting-similar-ends/submissions/1194717268
class Solution {
public:
    int minimumLength(string s) {
        int ans = 0, l = 0, r = (int)s.size() - 1;
        while(l < r) {
            char ch = s[l];
            bool flag = false;
            int nxt = l;
            while(nxt < s.size() && s[nxt] == ch) ++nxt;
            while(r >= l && s[r] == ch) -- r, flag = true;
            if(!flag) break;
            l = nxt;
        }
        return max(0, r - l + 1);
    }
};

/* Solution Description
*/

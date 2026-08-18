// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximum-score-after-splitting-a-string/submissions/1494505988
class Solution {
public:
    int maxScore(string s) {
        int l = s[0] == '0', r = 0;
        int N = (int)s.size();
        for(int i = 1; i < N; ++i)  if(s[i] == '1') ++ r;
        int ans = l + r;
        for(int i = 1; i < N - 1; ++i) {
            if(s[i] == '1') -- r;
            else ++ l;
            ans = max(ans, l + r);
        }
        return ans;
    }
};

/* Solution Description
*/

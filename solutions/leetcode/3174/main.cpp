// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/clear-digits/submissions/1537767050
class Solution {
public:
    string clearDigits(string s) {
        int N = (int)s.size(), r = -1;
        for(int i = 0; i < N; ++i) {
            if(isdigit(s[i])) r = max(r - 1, -1);
            else s[++ r] = s[i];
        }
        s.erase(s.begin() + r + 1, s.end());
        return s;
    }
};

/* Solution Description
*/

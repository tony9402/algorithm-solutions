// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/submissions/1224657360
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int N = (int)s.size();
        vector<int> erased(N);
        int cnt = 0;
        for(int i = 0; i < N; ++i) {
            char ch = s[i];
            if(ch == '(') ++ cnt;
            else if(ch == ')') {
                if(cnt == 0) {
                    erased[i] = 1;
                }
                else if(cnt > 0) {
                    -- cnt;
                }
            }
        }
        for(int i = N - 1; i >= 0; --i) {
            if(cnt == 0) break;
            if(erased[i]) continue;
            char ch = s[i];
            if(ch == '(') erased[i] = 1, -- cnt;
        }
        string ret;
        for(int i = 0; i < N; ++i) {
            if(erased[i]) continue;
            ret += s[i];
        }
        return ret;
    }
};

/* Solution Description
*/

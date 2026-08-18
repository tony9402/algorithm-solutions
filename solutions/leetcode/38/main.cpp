// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/count-and-say/submissions/1186228005
class Solution {
public:
    string countAndSay(int n) {
        string ans = "1";
        for(int i = 1; i < n; ++i) {
            string nxt = "";
            int cnt = 1;
            char pre = ans[0];
            for(int j = 1; j < (int)ans.size(); ++j) {
                if(pre == ans[j]) ++ cnt;
                else {
                    nxt += to_string(cnt);
                    nxt += pre;
                    cnt = 1;
                }
                pre = ans[j];
            }
            if(cnt) {
                nxt += to_string(cnt);
                nxt += pre;
            }
            swap(ans, nxt);
        }
        return ans;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/delete-characters-to-make-fancy-string/submissions/1439453218
class Solution {
public:
    string makeFancyString(string s) {
        char pre = -1;
        int cnt = 0, j = 0;
        for(int i = 0; i < s.size(); ++i) {
            char ch = s[i];
            if(pre == ch) {
                if(++ cnt >= 3) continue;
                s[j ++] = ch;
            }
            else {
                pre = ch;
                cnt = 1;
                s[j ++] = ch;
            }
        }
        return s.substr(0, j);
    }
};

/* Solution Description
*/

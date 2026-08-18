// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/existence-of-a-substring-in-a-string-and-its-reverse/submissions/1205821256
class Solution {
public:
    bool isSubstringPresent(string s) {
        string t = s; reverse(t.begin(), t.end());
        int n = (int)s.size();
        for(int i = 0; i + 1 < n; ++i) {
            auto it = s.substr(i, 2);
            for(int j = 0; j + 1 < n; ++j) {
                if(t.substr(j, 2) == it)return true;
            }
        }
        return false;
    }
};

/* Solution Description
*/

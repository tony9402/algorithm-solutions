// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/submissions/1532489836
class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        int cnt = 0;
        vector<int> cnt2(26);
        for(int i = 0; i < (int)s1.size(); ++i) {
            cnt += s1[i] != s2[i];
            ++ cnt2[s1[i] - 'a'];
            -- cnt2[s2[i] - 'a'];
        }
        bool flag = true;
        for(int i = 0; i < 26; ++i) {
            if(cnt2[i] != 0) flag = false;
        }
        flag &= (cnt <= 2);
        return flag;
    }
};

/* Solution Description
*/

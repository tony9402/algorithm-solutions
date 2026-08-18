// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/first-unique-character-in-a-string/submissions/1191114534
class Solution {
public:
    int firstUniqChar(string s) {
        int cnt[26] = {};
        for(int i = 0; i < 26; ++i) cnt[i] = INT_MAX;
        for(int i = 0; i < s.size(); ++i) {
            int &ret = cnt[s[i] - 'a'];
            if(ret == INT_MAX - 1) { ; }
            else if(ret == INT_MAX) { ret = i; }
            else ret = INT_MAX - 1;
        }
        int mn = *min_element(cnt, cnt + 26);
        return mn >= INT_MAX - 1 ? -1 : mn;
    }
};

/* Solution Description
*/

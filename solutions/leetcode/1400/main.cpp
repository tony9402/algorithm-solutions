// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/construct-k-palindrome-strings/submissions/1504943451
class Solution {
public:
    bool canConstruct(string s, int k) {
        int cnt = 0;
        for(const char &ch: s) cnt ^= 1 << (ch - 'a');
        return s.size() >= k && __builtin_popcount(cnt) <= k;
    }
};

/* Solution Description
*/

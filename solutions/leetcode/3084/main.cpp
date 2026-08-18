// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/count-substrings-starting-and-ending-with-given-character/submissions/1205824952
class Solution {
public:
    long long countSubstrings(string s, char c) {
        int cnt = 0;
        for(char ch: s) if(ch == c) cnt ++;
        return 1LL * cnt * (cnt + 1) / 2;
    }
};

/* Solution Description
*/

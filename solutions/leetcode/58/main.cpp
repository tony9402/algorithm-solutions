// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/length-of-last-word/submissions/1220230140
class Solution {
public:
    int lengthOfLastWord(string s) {
        int answer = 0, idx = s.size() - 1;
        while(idx >= 0 && s[idx] == ' ') -- idx;
        while(idx >= 0 && s[idx] != ' ') -- idx, ++ answer;
        return answer;
    }
};

/* Solution Description
*/

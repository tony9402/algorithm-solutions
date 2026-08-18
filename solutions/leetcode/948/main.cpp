// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/bag-of-tokens/submissions/1193194935
class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(tokens.begin(), tokens.end());
        int l = 0, r = (int)tokens.size() - 1;
        int score = 0, mx = 0;
        while(l <= r) {
            if(power >= tokens[l]) {
                mx = max(mx, ++ score);
                power -= tokens[l ++];
            }
            else if(score >= 1) {
                -- score;
                power += tokens[r --];
            }
            else break;
        }
        return mx;
    }
};

/* Solution Description
*/

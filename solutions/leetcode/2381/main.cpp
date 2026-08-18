// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/shifting-letters-ii/submissions/1498555540
class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        int N = (int)s.size();
        vector<int> P(N + 1);
        for(const vector<int> &shift: shifts) {
            int start = shift[0];
            int end = shift[1];
            int direction = 2 * shift[2] - 1;
            P[start] += direction;
            P[end + 1] -= direction;
        }
        int cur = 0;
        for(int i = 0; i < N; ++i) {
            cur = (cur + P[i] % 26 + 26) % 26;
            s[i] = (char)((s[i] - 'a' + cur) % 26 + 'a');
        }
        return s;
    }
};

/* Solution Description
*/

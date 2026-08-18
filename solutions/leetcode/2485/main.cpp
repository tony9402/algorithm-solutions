// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-the-pivot-integer/submissions/1202182014
class Solution {
public:
    int pivotInteger(int n) {
        int x = n * (n + 1) / 2;
        int sq = sqrt(x);
        return sq * sq == x ? sq : -1;
    }
};

/* Solution Description
*/

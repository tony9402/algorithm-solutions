// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/count-total-number-of-colored-cells/submissions/1563115128
class Solution {
public:
    long long coloredCells(int n) {
        if(n == 1) return 1;
        return 1 + 2LL * n * (n - 1);
    }
};

/* Solution Description
*/

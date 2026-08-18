// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/power-of-four/submissions/1081884979
class Solution {
public:
    bool isPowerOfFour(int n) {
        long long x = (long long)(n);
        long long bits = 0x0000555555555555LL;
        return x >= 0 && (x & bits) == x && __builtin_popcount(x) == 1;
    }
};

/* Solution Description
*/

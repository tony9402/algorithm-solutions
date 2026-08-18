// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/sqrtx/submissions/1195624355
class Solution {
public:
    int mySqrt(int x) {
        int l = 0, r = 65535;
        while(l <= r) {
            int mid = (l + r) / 2;
            if(1LL * mid * mid <= x) l = mid + 1;
            else r = mid - 1;
        }
        return r;
    }
};

/* Solution Description
*/

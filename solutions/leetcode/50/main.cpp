// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/powx-n/submissions/1188231848
class Solution {
public:
    double myPow(double x, int n) {
        if(n == 0) return 1.;
        if(n < 0) {
            if(n == INT_MIN) return 1. / x / myPow(x, -(n + 1));
            return 1. / myPow(x, -n);
        }
        if(n % 2 == 0) return myPow(x * x, n / 2);
        return x * myPow(x * x, n / 2);
    }
};

/* Solution Description
*/

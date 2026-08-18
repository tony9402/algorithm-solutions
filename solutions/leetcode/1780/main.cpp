// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/submissions/1562436693
class Solution {
public:
    bool checkPowersOfThree(int n) {
        while(n) {
            int cur = n % 3;
            if(cur == 2) return false;
            n /= 3;
        }
        return true;
    }
};

/* Solution Description
*/

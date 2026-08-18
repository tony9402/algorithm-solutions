// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/power-of-three/submissions/324199679
class Solution {
public:
    bool isPowerOfThree(int n) {
        return n > 0 && 1162261467 % n == 0;
    }
};

/* Solution Description
*/

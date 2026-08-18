// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/smallest-number-with-all-set-bits/submissions/1814568300
class Solution {
public:
    int smallestNumber(int n) {
        return ~0u>>__builtin_clz(n);
    }
};

/* Solution Description
*/

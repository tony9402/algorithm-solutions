// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/neighboring-bitwise-xor/submissions/1511108664
class Solution {
public:
    bool doesValidArrayExist(vector<int>& derived) {
        return accumulate(derived.begin(), derived.end(), 0, bit_xor<>()) == 0;
    }
};

/* Solution Description
*/

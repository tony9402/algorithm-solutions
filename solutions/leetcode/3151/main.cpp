// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/special-array-i/submissions/1527025491
class Solution {
public:
    bool isArraySpecial(vector<int>& nums) {
        int N = (int)nums.size();
        for(int i = 1; i < N; ++i) {
            if(~(nums[i] ^ nums[i - 1]) & 1) return false;
        }
        return true;
    }
};

/* Solution Description
*/

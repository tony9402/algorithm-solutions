// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/single-number/submissions/318149761
static int __=[](){std::ios::sync_with_stdio(false);return 0;}();
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        for(int i=1;i<nums.size();i++)
            nums[0] ^= nums[i];
        return nums[0];
    }
};

/* Solution Description
*/

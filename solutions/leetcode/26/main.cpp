// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/remove-duplicates-from-sorted-array/submissions/1187632009
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        int pre = -10000, k = 0;
        for(int i = 0; i < n; ++i) {
            if(pre != nums[i]) nums[k ++] = nums[i];
            pre = nums[i];
        }
        return k;
    }
};

/* Solution Description
*/

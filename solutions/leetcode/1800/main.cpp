// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximum-ascending-subarray-sum/submissions/1530803636
class Solution {
public:
    int maxAscendingSum(vector<int>& nums) {
        int ans = 0, sum = nums[0];
        for(int i = 1; i < (int)nums.size(); ++i) {
            if(nums[i - 1] < nums[i]) sum += nums[i];
            else ans = max(ans, sum), sum = nums[i];
        }
        ans = max(ans, sum);
        return ans;
    }
};

/* Solution Description
*/

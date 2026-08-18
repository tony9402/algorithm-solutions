// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/submissions/1556644155
class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int N = (int)nums.size();
        int sum = 0, sum2 = 0, mx = INT_MIN;
        for(int i = 0; i < N; ++i) {
            sum += nums[i];
            sum2 -= nums[i];
            if(sum < nums[i]) sum = nums[i];
            if(sum2 < -nums[i]) sum2 = -nums[i];
            mx = max({mx, sum, sum2, nums[i], -nums[i]});
        }
        return mx;
    }
};

/* Solution Description
*/

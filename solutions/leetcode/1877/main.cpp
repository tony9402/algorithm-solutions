// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/submissions/1100458171
class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ans = 0;
        int N = (int)nums.size();
        for(int i = 0; i < N; ++i) {
            ans = max(ans, nums[i] + nums[N - 1 - i]);
        }
        return ans;
    }
};

/* Solution Description
*/

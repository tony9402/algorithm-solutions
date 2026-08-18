// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/partition-equal-subset-sum/submissions/1599256200
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum % 2) return false;
        vector<int> DP(sum + 1);
        DP[0] = 1;
        sort(nums.begin(), nums.end());
        int N = (int)nums.size();
        for(int i = 0; i < N; ++i) {
            for(int j = sum; j >= nums[i]; --j) {
                DP[j] |= DP[j - nums[i]];
            }
        }
        return DP[sum / 2] == 1;
    }
};

/* Solution Description
*/

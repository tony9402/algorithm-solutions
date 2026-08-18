// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/longest-nice-subarray/submissions/1577576529
class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int N = (int)nums.size();
        int ans = 0, bit = 0;
        for(int i = 0, r = -1; i < N; ++i) {
            while(r + 1 < N && (bit & nums[r + 1]) == 0) bit |= nums[++r];
            ans = max(ans, r - i + 1);
            bit &= ~nums[i];
        }
        return ans;
    }
};

/* Solution Description
*/

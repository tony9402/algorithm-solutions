// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/submissions/1595030428
class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        long long ans = 0;
        int N = (int)nums.size();
        int mx = 0, mx2 = 0;
        for(int i = 0; i < N; ++i) {
            ans = max(ans, 1LL * mx2 * nums[i]);
            mx2 = max(mx2, mx - nums[i]);
            mx = max(mx, nums[i]);
        }
        return ans;
    }
};

/* Solution Description
*/

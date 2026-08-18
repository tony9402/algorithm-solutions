// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/subarray-product-less-than-k/submissions/1215372630
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int N = (int)nums.size(), ret = 1, ans = 0;
        for(int i = 0, r = -1; i < N; ++i) {
            r = max(r, i - 1);
            while(r + 1 < N && ret * nums[r + 1] < k) ret *= nums[++r];
            ans += max(0, r - i + 1);
            if(i <= r) ret /= nums[i];
        }
        return ans;
    }
};
int init = [] {
    ios_base::sync_with_stdio(false);  cin.tie(nullptr);
    return 0;
}();

/* Solution Description
*/

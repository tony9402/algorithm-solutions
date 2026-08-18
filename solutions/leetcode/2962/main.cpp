// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/submissions/1217566153
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        long long ans = 0;
        int N = (int)nums.size(), mx = *max_element(nums.begin(), nums.end());
        int l = 0, r = 0, cnt = 0;
        while(r < N) {
            if(nums[r] == mx) ++ cnt;
            while(cnt >= k) {
                if(nums[l] == mx) -- cnt;
                ++ l;
                ans += N - r;
            }
            ++ r;
        }
        return ans;
    }
};

/* Solution Description
*/

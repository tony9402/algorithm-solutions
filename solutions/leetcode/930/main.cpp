// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/binary-subarrays-with-sum/submissions/1203316026
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int N = (int)nums.size();
        vector<int> p(N + 1);
        vector<int> cnt(N + 1);
        for(int i = 0; i < N; ++i) {
            p[i + 1] = p[i] + nums[i];
            ++ cnt[p[i + 1]];
        }
        int ans = 0;
        for(int i = 1; i <= N; ++i) {
            if(p[i - 1] + goal <= N) ans += cnt[p[i - 1] + goal];
            -- cnt[p[i]];
        }
        return ans;
    }
};

/* Solution Description
*/

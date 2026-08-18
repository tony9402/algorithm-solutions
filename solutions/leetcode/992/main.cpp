// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/subarrays-with-k-different-integers/submissions/1218306059
class Solution {
public:
    int solve(vector<int> &nums, int k) {
        int ret = 0, N = (int)nums.size();
        unordered_map<int, int> mp;
        for(int i = 0, l = 0; i < N; ++i) {
            ++ mp[nums[i]];
            while(l <= i && mp.size() > k) {
                if(-- mp[nums[l]] == 0) mp.erase(nums[l]);
                ++ l;
            }
            ret += i - l;
        }
        return ret;
    }
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return solve(nums, k) - solve(nums, k - 1);
    }
};

/* Solution Description
*/

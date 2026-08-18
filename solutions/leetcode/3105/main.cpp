// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/submissions/1529355261
class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int mx = 0;
        int N = (int)nums.size();
        int cnt = 1, cnt2 = 1;
        for(int i = 1; i < N; ++i) {
            if(nums[i] > nums[i - 1]) ++ cnt;
            else mx = max(mx, cnt), cnt = 1;
            if(nums[i - 1] > nums[i]) ++ cnt2;
            else mx = max(mx, cnt2), cnt2 = 1;
        }
        mx = max({mx, cnt, cnt2});
        return mx;
    }
};

/* Solution Description
*/

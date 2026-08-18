// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/submissions/1528285388
class Solution {
public:
    bool check(vector<int>& nums) {
        int N = (int)nums.size(), cnt = 0;
        int mx = 0;
        for(int i = 1; i < 2 * N; ++i) {
            if(nums[(i - 1) % N] <= nums[i % N]) ++ cnt;
            else cnt = 0;
            mx = max(mx, cnt);
        }
        return mx >= N - 1;
    }
};

/* Solution Description
*/

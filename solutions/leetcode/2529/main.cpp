// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximum-count-of-positive-integer-and-negative-integer/submissions/1571080793
class Solution {
public:
    int maximumCount(vector<int>& nums) {
        int l = lower_bound(nums.begin(), nums.end(), 0) - nums.begin();
        int r = nums.end() - upper_bound(nums.begin(), nums.end(), 0);
        return max(l, r);
    }
};

/* Solution Description
*/

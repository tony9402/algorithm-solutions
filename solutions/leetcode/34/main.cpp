// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/submissions/1831824415
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.empty()) return {-1, -1};
        auto it = lower_bound(nums.begin(), nums.end(), target);
        auto it2 = upper_bound(nums.begin(), nums.end(), target);
        if(it == nums.end() || *it != target) return {-1, -1};
        return {(int)(it-nums.begin()), (int)(it2-nums.begin()-1)};
    }
};

/* Solution Description
*/

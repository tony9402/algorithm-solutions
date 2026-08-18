// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/remove-element/submissions/1187632792
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int k = 0, n = nums.size();
        for(int i = 0; i < n; ++i) {
            if(nums[i] != val) nums[k ++] = nums[i];
        }
        return k;
    }
};

/* Solution Description
*/

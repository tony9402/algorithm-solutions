// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/327113607
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;

        while(l <= r) {
            int mid = (l + r) >> 1;

            if(nums[mid] == target) return mid;
            else if(nums[mid] > target) {
                if(nums[r] < nums[mid] && target <= nums[r]) l = mid + 1;
                else r = mid - 1;
            } else {
                if(nums[mid] < nums[l] && target >= nums[l]) r = mid - 1;
                else l = mid + 1;
            }
        }

        return -1;
    }
};

/* Solution Description
*/

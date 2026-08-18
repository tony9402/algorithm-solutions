// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/largest-perimeter-triangle/submissions/820904364
class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int N = (int)nums.size();
        int ans = 0;
        for(int i = N - 1; i > 1; --i){
            if(nums[i - 2] + nums[i - 1] > nums[i]) {
                ans = nums[i - 2] + nums[i - 1] + nums[i];
                break;
            }
        }
        return ans;
    }
};

/* Solution Description
*/

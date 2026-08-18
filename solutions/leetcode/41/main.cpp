// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/first-missing-positive/submissions/1214070136
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int N = (int)nums.size();
        for(int i = 0; i < N; ++i) {
            while(1 <= nums[i] && nums[i] <= N && nums[nums[i] - 1] != nums[i]) {
                swap(nums[nums[i] - 1], nums[i]);
            }
        }
        int ans = N + 1;
        for(int i = 0; i < N; ++i) {
            if(nums[i] != i + 1) {
                ans = i + 1;
                break;
            }
        }
        return ans;
    }
};

/* Solution Description
*/

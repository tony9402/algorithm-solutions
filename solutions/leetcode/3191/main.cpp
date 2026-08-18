// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/submissions/1578522046
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ans = 0;
        int N = (int)nums.size();
        for(int i = 0; i + 2 < N; ++i) {
            if(nums[i] == 0) {
                nums[i] = 1 - nums[i];
                nums[i + 1] = 1 - nums[i + 1];
                nums[i + 2] = 1 - nums[i + 2];
                ++ ans;
            }
        }
        if(nums[N - 1] == 1 && nums[N - 2] == 1) return ans;
        return -1;
    }
};

/* Solution Description
*/

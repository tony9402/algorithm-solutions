// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/apply-operations-to-an-array/submissions/1559256750
class Solution {
public:
    vector<int> applyOperations(vector<int>& nums) {
        int N = (int)nums.size();
        vector<int> answer(N);
        for(int i = 0; i + 1 < N; ++i) {
            if(nums[i] == nums[i + 1]) {
                nums[i] *= 2;
                nums[i + 1] = 0;
            }
        }
        int i, j;
        for(i = 0, j = 0; i < N; ++i) {
            if(nums[i]) nums[j ++] = nums[i];
        }
        while(j < N) nums[j ++] = 0;
        return nums;
    }
};

/* Solution Description
*/

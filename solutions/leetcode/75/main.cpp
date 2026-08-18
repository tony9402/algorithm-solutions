// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/sort-colors/submissions/1183610679
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int k = 0, N = (int)nums.size();
        for(int t = 0; t < 3; ++t) {
            for(int i = 0; i < N; ++i) {
                if(nums[i] == t) swap(nums[i], nums[k ++]);
            }
        }
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/n-repeated-element-in-size-2n-array/submissions/1872469892
class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        int N = (int)nums.size();
        if(N < 6) {
            unordered_map<int, int> mp;
            for(const int &x: nums) {
                if(++ mp[x] == N / 2) return x;
            }
        }
        for(int i = 2; i < N; ++i) {
            if(nums[i - 1] == nums[i] || nums[i - 2] == nums[i]) return nums[i];
        }
        return -1;
    }
};

/* Solution Description
*/

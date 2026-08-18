// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-index-of-a-valid-split/submissions/1588205850
class Solution {
public:
    int minimumIndex(vector<int>& nums) {
        unordered_map<int, int> L, R;
        int N = (int)nums.size();
        for(const int &x: nums)  ++ R[x];
        for(int i = 0; i < N; ++i) {
            int x = nums[i];
            -- R[x]; ++ L[x];
            if(L[x] * 2 > i + 1 && R[x] * 2 > N - i - 1) return i;
        }
        return -1;
    }
};

/* Solution Description
*/

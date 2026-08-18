// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-number-of-operations-to-make-elements-in-array-distinct/submissions/1600176084
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int cnt[101]{}, N = (int)nums.size(), answer = 0;
        int cnt2 = 0;
        for(int i = 0; i < N; ++i) if(++ cnt[nums[i]] == 2) ++cnt2;
        for(int i = 0; cnt2 > 0 && i < N; i += 3) {
            for(int j = 0; j < 3 && i + j < N; ++j) {
                if(--cnt[nums[i + j]] == 1) -- cnt2;
            }
            ++ answer;
        }
        return answer;
    }
};

/* Solution Description
*/

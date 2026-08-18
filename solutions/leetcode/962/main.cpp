// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximum-width-ramp/submissions/1417931065
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        int N = (int)nums.size();
        int M = 50001;
        vector<int> L(M + 1, N + 1), R(M + 1, -1);
        for(int i = 0; i < N; ++i) {
            L[nums[i]] = min(L[nums[i]], i);
            R[nums[i]] = i;
        }
        for(int i = M - 1; i >= 0; --i) R[i] = max(R[i + 1], R[i]);
        int answer = 0;
        for(int i = 0; i < N; ++i)  answer = max(answer, R[nums[i]] - L[nums[i]]);
        return answer;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/largest-divisible-subset/submissions/1598424058
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int N = (int)nums.size();
        sort(nums.begin(), nums.end());
        vector<int> pre(N, -1), DP(N, 1);

        int mx = 0, idx = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = i + 1; j < N; ++j) {
                if(nums[j] % nums[i] == 0 && DP[j] < DP[i] + 1) {
                    pre[j] = i;
                    DP[j] = DP[i] + 1;
                }
            }
            if(mx < DP[i]) {
                mx = DP[i];
                idx = i;
            }
        }

        vector<int> answer;
        while(idx != -1) {
            answer.push_back(nums[idx]);
            idx = pre[idx];
        }
        return answer;
    }
};

/* Solution Description
*/

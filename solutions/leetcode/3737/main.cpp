// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/count-subarrays-with-majority-element-i/submissions/2045151856
class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        int N = (int)nums.size();
        vector<int> P(N + 1, 0);
        for(int i = 0; i < N; ++i) P[i + 1] = (nums[i] == target ? 1 : -1);
        for(int i = 1; i <= N; ++i) P[i] += P[i - 1];
        int ans = 0;
        for(int i = 1; i <= N; ++i) {
            for(int j = i; j <= N; ++j) {
                if(P[j] - P[i - 1] > 0) ++ ans;
            }
        }
        return ans;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/submissions/1594501262
class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        int N = (int)nums.size();
        long long ans = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = i + 1; j < N; ++j) {
                for(int k = j + 1; k < N; ++k) {
                    long long x = 1LL * (nums[i] - nums[j]) * nums[k];
                    if(x < 0) x = 0;
                    ans = max(ans, x);
                }
            }
        }
        return ans;
    }
};

/* Solution Description
*/

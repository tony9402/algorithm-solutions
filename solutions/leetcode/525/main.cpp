// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/contiguous-array/submissions/1204908341
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int N = (int)nums.size();
        vector<int> idx(2 * N + 1, -2);
        idx[N] = -1;
        int ans = 0, S = 0;
        for(int i = 0; i < N; ++i) {
            S += nums[i] ? 1 : -1;
            if(idx[S + N] == -2) idx[S + N] = i;
            else ans = max(ans, i - idx[S + N]);
        }
        return ans;
    }
};
auto _=[]() {ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);return 0;}();

/* Solution Description
*/

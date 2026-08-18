// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/number-of-ways-to-split-array/submissions/1495726750
using ll = long long;

class Solution {
public:
    int waysToSplitArray(vector<int>& nums) {
        int N = (int)nums.size();
        vector<ll> P(N + 2);
        for(int i = 1; i <= N; ++i) P[i] = P[i - 1] + nums[i - 1];
        auto Sum = [&](int idx) -> pair<ll, ll> {
            return make_pair(P[idx + 1], P[N] - P[idx + 1]);
        };
        int ans = 0;
        for(int i = 0; i < N - 1; ++i) {
            auto [l, r] = Sum(i);
            if(l >= r) ++ ans;
        }
        return ans;
    }
};

/* Solution Description
*/

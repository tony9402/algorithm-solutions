// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximum-strength-of-k-disjoint-subarrays/submissions/1199213832
class Solution {
public:
    using ll = long long;
    long long maximumStrength(vector<int>& nums, int k) {
        int N = (int)nums.size();
        const ll INF = LLONG_MIN;
        vector<vector<vector<ll>>> DP(2, vector<vector<ll>>(k + 1, vector<ll>(N + 1, INF)));
        DP[1][1][1] = 1LL * nums[0] * k;
        ll ans = INF;
        if(k == 1) ans = DP[1][1][1];
        for(ll i = 2; i <= N; ++i) {
            for(ll j = 1; j <= k; ++j) {
                DP[0][j][i] = max(DP[1][j - 1][i - 1], DP[0][j - 1][i - 1]);
                ll x = 1LL * nums[i - 1] * (k + 1 - j) * (j % 2 ? 1 : -1);
                if(j == 1) DP[1][j][i] = x;
                if(DP[1][j][i - 1] != INF) DP[1][j][i] = max(DP[1][j][i], DP[1][j][i - 1] + x);
                if(DP[1][j - 1][i - 1] != INF) DP[1][j][i] = max(DP[1][j][i], DP[1][j - 1][i - 1] + x);
                if(j == k) ans = max(ans, DP[1][j][i]);
            }
        }
        return ans;
    }
};

/* Solution Description
*/

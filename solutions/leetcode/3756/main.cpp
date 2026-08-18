// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-ii/submissions/2059849054
using ll = long long;
const ll MOD = 1e9 + 7;

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int N = (int)s.size();
        vector<ll> prefix_sum(N + 1), prefix_concat(N + 1);
        vector<int> cnt(N + 1);
        vector<ll> pw(N + 1, 1);
        for(int i = 1; i <= N; ++i) pw[i] = pw[i - 1] * 10 % MOD;
        for(int i = 1; i <= N; ++i) {
            int x = s[i - 1] - 48;
            prefix_sum[i] = prefix_sum[i - 1] + x;
            if(x != 0) {
                prefix_concat[i] = (prefix_concat[i - 1] * 10 % MOD + x) % MOD;
                cnt[i] = cnt[i - 1] + 1;
            }
            else {
                prefix_concat[i] = prefix_concat[i - 1];
                cnt[i] = cnt[i - 1];
            }
        }
        int Q = (int)queries.size();
        vector<int> answer;
        for(int i = 0; i < Q; ++i) {
            int l = queries[i][0] + 1;
            int r = queries[i][1] + 1;
            int sum = prefix_sum[r] - prefix_sum[l - 1];
            int c = cnt[r] - cnt[l - 1];
            ll ret = (prefix_concat[r] - pw[c] * prefix_concat[l - 1] % MOD) % MOD;
            if(ret < 0) ret += MOD;
            ret = ret * sum % MOD;
            answer.push_back(ret);
        }
        return answer;
    }
};

/* Solution Description
*/

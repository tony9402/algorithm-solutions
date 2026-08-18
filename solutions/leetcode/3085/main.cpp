// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/submissions/1205958631
class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int> _cnt(26);
        for(char ch: word) _cnt[ch - 'a'] ++;
        const int INF = INT_MAX / 2;
        vector<int> cnt;
        for(int i = 0; i < 26; ++i) if(_cnt[i]) cnt.push_back(_cnt[i]);
        sort(cnt.begin(), cnt.end());
        int K = (int)cnt.size();
        vector<vector<int>> dp(K, vector<int>(K, INF + 1));
        function<int(int, int)> go = [&](int l, int r) -> int {
            if(l > r) return INF;
            int &ret = dp[l][r];
            if(l == r) return ret = 0;
            if(cnt[r] - cnt[l] <= k) return ret = 0;
            if(ret != INF + 1) return ret;
            ret = min(go(l + 1, r) + cnt[l], go(l, r - 1) + cnt[r] - (cnt[l] + k));

            return ret;
        };
        return go(0, K - 1);
    }
};

/* Solution Description
*/

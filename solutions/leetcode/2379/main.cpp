// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/submissions/1566721809
class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int N = (int)blocks.size();
        vector<int> cnt(N + 1);
        for(int i = 1; i <= N; ++i) {
            cnt[i] = cnt[i - 1] + (blocks[i - 1] == 'W');
        }
        int ans = INT_MAX;
        for(int i = k; i <= N; ++i) {
            if(cnt[i] - cnt[i - k] < ans) ans = cnt[i] - cnt[i - k];
        }
        return ans;
    }
};

/* Solution Description
*/

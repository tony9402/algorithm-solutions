// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-missing-and-repeated-values/submissions/1564338966
class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        int N = (int)grid.size();
        vector<int> cnt(N * N + 1);
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                int x = grid[i][j];
                ++ cnt[x];
            }
        }
        vector<int> ans(2);
        for(int i = 1; i <= N * N; ++i) {
            if(cnt[i] == 0) ans[1] = i;
            if(cnt[i] > 1) ans[0] = i;
        }
        return ans;
    }
};

/* Solution Description
*/

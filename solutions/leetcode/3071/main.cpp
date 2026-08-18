// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-operations-to-write-the-letter-y-on-a-grid/submissions/1192146569
class Solution {
public:
    int minimumOperationsToWriteY(vector<vector<int>>& grid) {
        int N = (int)grid.size();
        int cnt[3]{}, cnt2[3]{};
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if(i <= N / 2) {
                    if(i == j || i == N - 1 - j) cnt[grid[i][j]]++;
                    else cnt2[grid[i][j]]++;
                }
                else {
                    if(j == N / 2) cnt[grid[i][j]]++;
                    else cnt2[grid[i][j]]++;
                }
            }
        }
        int S = cnt[0]+cnt[1]+cnt[2], S1 = cnt2[0]+cnt2[1]+cnt2[2];
        int ret = INT_MAX;
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                if(i == j) continue;
                ret = min(ret, S - cnt[i] + S1 - cnt2[j]);
            }
        }
        return ret;
    }
};

/* Solution Description
*/

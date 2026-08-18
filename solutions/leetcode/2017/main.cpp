// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/grid-game/submissions/1515665540
using ll = long long;
class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        int N = (int)grid[0].size();
        ll top = accumulate(grid[0].begin(), grid[0].end(), 0LL), bottom = 0;
        ll bot = 0;
        ll mn = LLONG_MAX;
        for(int i = 0; i < N; ++i) {
            top -= grid[0][i];
            mn = min(mn, max(top, bot));
            bot += grid[1][i];
        }
        return mn;
    }
};

/* Solution Description
*/

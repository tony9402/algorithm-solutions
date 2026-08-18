// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-path-sum/submissions/327097953
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if(grid.empty())return 0;
        const int h = grid.size(), w = grid[0].size();
        vector<vector<int>> dp;
        dp.resize(h);
        for(auto &i: dp)
            i.resize(w, 0x3f3f3f3f);
        dp[0][0] = grid[0][0];
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                if(i > 0)dp[i][j] = min(dp[i][j], dp[i-1][j] + grid[i][j]);
                if(j > 0)dp[i][j] = min(dp[i][j], dp[i][j-1] + grid[i][j]);
            }
        }
        return dp[h-1][w-1];
    }
};

/* Solution Description
*/

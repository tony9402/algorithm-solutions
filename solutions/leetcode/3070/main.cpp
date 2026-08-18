// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k/submissions/1192139075
class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int N = (int)grid.size();
        int M = (int)grid[0].size();
        int ans = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                if(i > 0) grid[i][j] += grid[i - 1][j];
                if(j > 0) grid[i][j] += grid[i][j - 1];
                if(i > 0 && j > 0) grid[i][j] -= grid[i - 1][j - 1];
                if(grid[i][j] <= k) ++ans;
            }
        }
        return ans;
    }
};

/* Solution Description
*/

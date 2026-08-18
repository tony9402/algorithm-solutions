// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/magic-squares-in-grid/submissions/1868910747
class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        function<bool(int, int)> chk = [&](int y, int x) -> bool {
            int sum = 0, cur = 0, bit = 0;
            for(int i = 0; i < 3; ++i) {
                for(int j = 0; j < 3; ++j) {
                    int v = grid[y + i][x + j];
                    if(1 <= v && v <= 9) bit |= 1 << (v - 1);
                    else return false;
                }
            }
            if(bit != 511) return false;
            for(int i = 0; i < 3; ++i) sum += grid[y + i][x + i];
            for(int i = 0; i < 3; ++i) cur += grid[y + i][x + 2 - i];
            if(sum != cur) return false;
            for(int i = 0; i < 3; ++i) {
                cur = 0;
                for(int j = 0; j < 3; ++j) cur += grid[y + i][x + j];
                if(sum != cur) return false;
                cur = 0;
                for(int j = 0; j < 3; ++j) cur += grid[y + j][x + i];
                if(sum != cur) return false;
            }
            return true;
        };
        int N = (int)grid.size(), M = (int)grid[0].size();
        int ans = 0;
        for(int i = 0; i < N - 2; ++i) {
            for(int j = 0; j < M - 2; ++j) {
                if(chk(i, j)) ++ ans;
            }
        }
        return ans;
    }
};

/* Solution Description
*/

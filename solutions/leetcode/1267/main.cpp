// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/count-servers-that-communicate/submissions/1517610320
class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int N = (int)grid.size();
        int M = (int)grid[0].size();
        int answer = 0;
        vector<int> A(N), B(M);
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                A[i] += grid[i][j];
                B[j] += grid[i][j];
            }
        }
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                if(grid[i][j] && (A[i] > 1 || B[j] > 1)) ++ answer;
            }
        }
        return answer;
    }
};

/* Solution Description
*/

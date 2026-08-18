// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/equal-sum-grid-partition-i/submissions/1958332922
using ll = long long;
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int N = (int)grid.size();
        int M = (int)grid[0].size();
        vector<ll> X(M), Y(N);
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                X[j] += grid[i][j];
                Y[i] += grid[i][j];
            }
        }
        for(int i = 1; i < N; ++i) Y[i] += Y[i - 1];
        for(int i = 1; i < M; ++i) X[i] += X[i - 1];
        for(int i = 1; i < N; ++i) {
            if(Y[i - 1] == Y[N - 1] - Y[i - 1]) return true;
        }
        for(int i = 1; i < M; ++i) {
            if(X[i - 1] == X[M - 1] - X[i - 1]) return true;
        }
        return false;
    }
};

/* Solution Description
*/

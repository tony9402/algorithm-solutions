// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/construct-product-matrix/submissions/1957455364
const int MOD = 12345;
int extgcd(int a, int b, int c, int d) {
    if(a == 1) return c;
    return extgcd(b, a % b, d, c - d * (a / b));
}
int modinv(int x) {
    int g = extgcd(MOD, x, 0, 1);
    if(g < 0) g += MOD;
    return g;
}
long long power(long long a, long long b) {
    if(b == 0) return 1;
    if(b % 2 == 0) return power(1LL * a * a % MOD, b >>= 1);
    return a * power(a, b - 1) % MOD;
}

class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int tot = 1;
        int N = (int)grid.size(), M = (int)grid[0].size();
        array<int, 3> D = {3, 5, 823};
        vector<vector<array<int, 3>>> cnt(N, vector<array<int, 3>>(M, {0, 0, 0}));
        array<int, 3> totCnt = {0, 0, 0};
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                for(int k = 0; k < 3; ++k) {
                    while(grid[i][j] % D[k] == 0) {
                        ++ cnt[i][j][k];
                        ++ totCnt[k];
                        grid[i][j] /= D[k];
                    }
                }
                tot = 1LL * tot * grid[i][j] % MOD;
            }
        }
        vector<vector<int>> answer(N, vector<int>(M));
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                bool flag = true;
                for(int k = 0; k < 3; ++k) {
                    if(totCnt[k] == cnt[i][j][k]) flag = false;
                }
                if(flag) continue;
                answer[i][j] = 1LL * tot * modinv(grid[i][j]) % MOD;
                for(int k = 0; k < 3; ++k) {
                    int x = totCnt[k] - cnt[i][j][k];
                    answer[i][j] = 1LL * answer[i][j] * power(D[k], x) % MOD;
                }
            }
        }
        return answer;
    }
};

/* Solution Description
*/

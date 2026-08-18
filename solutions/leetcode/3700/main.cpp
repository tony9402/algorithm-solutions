// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/number-of-zigzag-arrays-ii/submissions/2043971932
const int MOD = 1e9 + 7;
using ll = long long;
using Row = vector<ll>;
using Mat = vector<Row>;

Mat mul(const Mat &A, const Mat &B) {
    int N = (int)A.size();
    int M = (int)B[0].size();
    int K = (int)B.size();
    Mat ret(N, Row(M));

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            for(int k = 0; k < K; ++k) {
                ret[i][j] = (ret[i][j] + A[i][k] * B[k][j] % MOD) % MOD;
            }
        }
    }
    return ret;
}

Mat power(Mat base, int k) {
    int N = (int)base.size();
    Mat I = Mat(N, Row(N, 0));
    for(int i = 0; i < N; ++i) I[i][i] = 1;
    while(k > 0) {
        if(k & 1) I = mul(I, base);
        base = mul(base, base);
        k >>= 1;
    }
    return I;
}


class Solution {
public:
    int zigZagArrays(int N, int l, int r) {
        int sz = r - l + 1;

        Mat B = Mat(sz << 1, Row(sz << 1));

        function<int(int, int)> pos = [&](int a, int b) -> int { return a << 1 | b; };
        for(int i = 0; i < sz; ++i) {
            for(int j = 0; j < sz; ++j) {
                if(i < j) B[pos(i, 1)][pos(j, 0)] = 1;
                else if(i > j) B[pos(i, 0)][pos(j, 1)] = 1;
            }
        }

        Mat ret = power(B, N - 1);
        int ans = 0;
        int sz2 = sz << 1;
        for(int i = 0; i < sz2; ++i) {
            for(int j = 0; j < sz2; ++j) {
                ans = (ans + ret[i][j]) % MOD;
            }
        }
        return ans;
    }
};

/* Solution Description
*/

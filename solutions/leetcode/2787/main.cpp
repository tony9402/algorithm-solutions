// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/submissions/1732098664
class Solution {
public:
    int power(int a, int b) {
        if(b == 0) return 1;
        if(b % 2) return a * power(a, b - 1);
        int p = power(a, b / 2);
        return p * p;
    }
    int numberOfWays(int n, int x) {
        vector<int> DP(n + 1);

        const int MOD = 1e9 + 7;
        DP[0] = 1;
        for(int i = 1; ; ++i) {
            int p = power(i, x);
            if(p > n) break;
            for(int j = n; j - p >= 0; --j) {
                DP[j] = (DP[j] + DP[j - p]) % MOD;
            }
        }
        return DP[n];
    }
};

/* Solution Description
*/

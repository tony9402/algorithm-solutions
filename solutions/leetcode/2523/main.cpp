// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/closest-prime-numbers-in-range/submissions/1565479675
class Solution {
public:
    vector<int> closestPrimes(int left, int right) {
        const int mx = 1500000;
        vector<int> primes, chk(mx + 1, 1);
        chk[0] = chk[1] = 0;
        for(int i = 2; i <= mx; ++i) {
            if(chk[i] == 0) continue;
            primes.push_back(i);
            for(int j = i + i; j <= mx; j += i) {
                chk[j] = 0;
            }
        }
        int l = upper_bound(primes.begin(), primes.end(), left - 1) - primes.begin();
        int r = lower_bound(primes.begin(), primes.end(), right + 1) - primes.begin();
        if(r - l <= 1) return {-1, -1};
        int mn = INT_MAX;
        vector<int> ans(2);
        for(int i = l; i + 1 < r; ++i) {
            if(mn > primes[i + 1] - primes[i]) {
                mn = primes[i + 1] - primes[i];
                ans[0] = primes[i];
                ans[1] = primes[i + 1];
            }
        }
        return ans;
    }
};

/* Solution Description
*/

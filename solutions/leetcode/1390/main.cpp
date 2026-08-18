// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/four-divisors/submissions/1874110886
class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        vector<int> lo(100001);
        lo[1] = 1;
        for(int i = 2; i <= 100000; ++i) {
            if(lo[i] == 0) lo[i] = i;
            for(int j = i + i; j <= 100000; j += i) {
                if(lo[j] == 0) lo[j] = i;
            }
        }
        int ans = 0;
        for(int x: nums) {
            int cnt = 1;
            vector<pair<int, int>> factors;
            for(int j = x; j > 1; j /= lo[j]) {
                if(!factors.empty() && factors.back().first == lo[j]) ++ factors.back().second;
                else factors.emplace_back(lo[j], 1);
            }
            for(const auto &[factor, c]: factors)  cnt *= (c + 1);
            if(cnt != 4) continue;
            ans += 1 + x;
            if(factors.size() == 1) ans += (factors[0].first + 1) * factors[0].first;
            else ans += factors[0].first + factors[1].first;
        }
        return ans;
    }
};

/* Solution Description
*/

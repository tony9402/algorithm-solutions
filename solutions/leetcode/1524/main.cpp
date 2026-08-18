// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/submissions/1554744242
class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        int cnt = 0, sum = 0, N = (int)arr.size();
        for(const int &x: arr) {
            sum += x;
            if(sum % 2) ++ cnt;
        }
        return cnt * (1LL + N - cnt) % MOD;
    }
};

/* Solution Description
*/

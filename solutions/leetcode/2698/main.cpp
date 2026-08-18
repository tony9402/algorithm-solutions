// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-the-punishment-number-of-an-integer/submissions/1543502998
class Solution {
public:
    int punishmentNumber(int n) {
        int ans = 0;
        for(int i = 1; i <= n; ++i) {
            function<bool(const string&, int, int, int)> go = [&](const string &S, int idx, int sum, int last) -> bool {
                if(idx == S.size()) return sum + last == i;
                return go(S, idx + 1, sum, last * 10 + S[idx] - 48) || go(S, idx + 1, sum + last, S[idx] - 48);
            };
            if(go(to_string(i * i), 0, 0, 0)) ans += i * i;
        }
        return ans;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/harshad-number/submissions/1526133364
class Solution {
public:
    int sumOfTheDigitsOfHarshadNumber(int N) {
        string s = to_string(N);
        int d = 0;
        for(int i = 0; i < (int)s.size(); ++i) {
            int h = (int)(s[i] - '0');
            d += h;
        }
        if(N % d == 0) return d;
        return -1;
    }
};

/* Solution Description
*/

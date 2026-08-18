// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximum-possible-number-by-binary-concatenation/submissions/1505139403
class Solution {
public:
    string to_digit(int x) {
        string ret = "";
        while(x) {
            ret += to_string(x % 2);
            x /= 2;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
    int to_digit(string S) {
        int ret = 0;
        for(const char &ch: S) ret = ret << 1 | (ch - '0');
        return ret;
    }
    int maxGoodNumber(vector<int>& nums) {
        vector<string> digit;
        for(const int &x: nums) digit.push_back(to_digit(x));
        sort(digit.begin(), digit.end(), [&](string a, string b) -> bool {
            return a + b > b + a;
        });
        string x = "";
        for(const string &s: digit) x += s;
        return to_digit(x);
    }
};

/* Solution Description
*/

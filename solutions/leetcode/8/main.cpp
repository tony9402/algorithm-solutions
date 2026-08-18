// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/string-to-integer-atoi/submissions/1187345929
class Solution {
public:
    int myAtoi(string s) {
        long long ret = 0;
        bool minus = false, found = false;
        for(char ch: s) {
            if(ch == '-') {
                if(found) break;
                minus = true, found = true;
            }
            else if(ch == '+') {
                if(found) break;
                found = true;
            }
            else if('0' <= ch && ch <= '9') {
                found = true;
                ret = ret * 10 + ch - 48;
                if(minus && ret > 2147483648LL) ret = 2147483648;
                else if(!minus && ret > 2147483647LL)ret = 2147483647;
            }
            else if(ch == ' ') {
                if(found) break;
            }
            else break;
        }
        return minus ? -ret : ret;
    }
};

/* Solution Description
*/

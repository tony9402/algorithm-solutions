// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimize-xor/submissions/1508972226
class Solution {
public:
    int minimizeXor(int num1, int num2) {
        int cnt1 = __builtin_popcount(num1);
        int cnt2 = __builtin_popcount(num2);
        int x = 0, b = 1 << 30, used = 0;
        while(used < min(cnt1, cnt2)) {
            if(num1 & b) {
                x |= b;
                ++ used;
            }
            b >>= 1;
        }
        b = 1;
        while(used < cnt2) {
            if(~x & b) {
                x |= b;
                ++ used;
            }
            b <<= 1;
        }
        return x;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/submissions/1550116550
class Solution {
public:
    string getHappyString(int n, int k) {
        int sz = 3 * (1 << (n - 1));
        if(k > sz) return "";
        auto [a, b] = div(k - 1, 1 << (n - 1));
        string s(n, ' ');
        s[0] = 'a' + a;
        bitset<9> bit(b);
        string db = "bcacab";
        for(int i = n - 2; i >= 0; --i) {
            char idx = s[n - 2 - i] - 'a';
            s[n - 1 - i] = bit[i] ? db[idx * 2 + 1] : db[idx * 2];
        }
        return s;
    }
};

/* Solution Description
*/

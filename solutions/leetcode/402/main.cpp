// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/remove-k-digits/submissions/1229362532
class Solution {
public:
    string removeKdigits(string num, int k) {
        stack<char> st;
        for(char ch: num) {
            while(k > 0 && !st.empty() && st.top() > ch) st.pop(), --k;
            st.push(ch);
        }
        string ret = "";
        while(!st.empty()) ret += st.top(), st.pop();
        while(!ret.empty() && ret.back() == '0') ret.pop_back();
        reverse(ret.begin(), ret.end());
        while(!ret.empty() && k > 0) ret.pop_back(), --k;
        if(ret.empty()) ret = "0";
        return ret;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/longest-valid-parentheses/submissions/1188592342
class Solution {
public:
    int longestValidParentheses(string s) {
        int N = (int)s.size();
        stack<int> st; st.push(-1);
        int mx = 0;
        for(int i = 0; i < N; ++i) {
            char ch = s[i];
            if(st.top() != -1 && s[st.top()] == '(' && ch == ')') {
                st.pop(), mx = max(mx, i - st.top());
            }
            else st.push(i);
        }
        return mx;
    }
};

/* Solution Description
*/

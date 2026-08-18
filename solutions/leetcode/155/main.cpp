// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/min-stack/submissions/1883282222
class MinStack {
public:
    stack<int> st, monotone_stack;
    MinStack() {}

    void push(int val) {
        st.push(val);
        if(monotone_stack.empty() || monotone_stack.top() >= val) {
            monotone_stack.push(val);
        }
    }

    void pop() {
        int x = st.top(); st.pop();
        if(monotone_stack.top() == x) monotone_stack.pop();
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return monotone_stack.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

/* Solution Description
*/

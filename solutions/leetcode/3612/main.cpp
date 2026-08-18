// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/process-string-with-special-operations-i/submissions/2034468862
class Solution {
public:
    string processStr(string s) {
        deque<char> dq;
        bool changed = false;
        for(char ch: s) {
            if(ch == '#') { // 최악 2^19 만큼 길어지긴 하는데 문제 없음
                int cnt = dq.size();
                for(int i = 0; i < cnt; ++i) {
                    if(changed) {
                        dq.push_front(dq[(int)(dq.size() - 1 - i)]);
                    }
                    else {
                        dq.push_back(dq[i]);
                    }
                }
            }
            else if(ch == '*') {
                if(!dq.empty()) {
                    if(changed) dq.pop_front();
                    else dq.pop_back();
                }
            }
            else if(ch == '%') {
                changed = !changed;
            }
            else {
                if(changed) dq.push_front(ch);
                else dq.push_back(ch);
            }
        }

        string answer = "";
        int N = (int)dq.size();
        if(changed) {
            for(int i = N - 1; i >= 0; --i) answer += dq[i];
        }
        else {
            for(int i = 0; i < N; ++i) answer += dq[i];
        }
        return answer;
    }
};

/* Solution Description
*/

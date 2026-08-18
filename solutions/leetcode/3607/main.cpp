// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/power-grid-maintenance/submissions/1822570895
class Solution {
public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        vector<int> uf(c + 1, -1);
        function<int(int)> find = [&](int x) -> int { return uf[x] < 0 ? x : uf[x] = find(uf[x]); };

        vector<int> offline(c + 1);
        vector<priority_queue<int, vector<int>, greater<int>>> pqs(c + 1);

        function<bool(int, int)> merge = [&](int u, int v) -> int {
            u = find(u); v = find(v);
            if(u == v) return false;
            uf[v] = u;
            return true;
        };
        function<int(int)> getAnswer = [&](int x) -> int {
            x = find(x);
            while(!pqs[x].empty() && offline[pqs[x].top()]) pqs[x].pop();
            return pqs[x].empty() ? -1 : pqs[x].top();
        };
        vector<vector<int>> G(c + 1);
        for(int i = 0; i < (int)connections.size(); ++i) {
            int u = connections[i][0], v = connections[i][1];
            merge(u, v);
        }
        for(int i = 1; i <= c; ++i) pqs[find(i)].push(i);
        vector<int> answer;
        for(int i = 0; i < (int)queries.size(); ++i) {
            int cmd = queries[i][0], x = queries[i][1];
            if(cmd == 2) offline[x] = 1;
            else {
                if(offline[x] == 0) answer.push_back(x);
                else answer.push_back(getAnswer(x));
            }
        }
        return answer;
    }
};

/* Solution Description
*/

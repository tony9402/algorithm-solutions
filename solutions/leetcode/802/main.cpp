// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-eventual-safe-states/submissions/1519152641
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int N = (int)graph.size();
        vector<vector<int>> rG(N);
        vector<int> ind(N);
        for(int i = 0; i < N; ++i) {
            for(int prv: graph[i]) {
                rG[prv].push_back(i);
                ++ ind[i];
            }
        }
        queue<int> Q;
        vector<int> chk(N);
        for(int i = 0; i < N; ++i) {
            if(ind[i] == 0) Q.push(i), chk[i] =  1;
        }
        while(!Q.empty()) {
            int cur = Q.front(); Q.pop();
            for(int nxt: rG[cur]) {
                if(--ind[nxt] == 0) Q.push(nxt), chk[nxt] |= chk[cur];
            }
        }
        vector<int> answer;
        for(int i = 0; i < N; ++i) {
            if(chk[i]) answer.push_back(i);
        }
        return answer;
    }
};

/* Solution Description
*/

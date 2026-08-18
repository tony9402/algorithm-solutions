// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/parallel-courses-iii/submissions/1077994047
class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<vector<int>> G(n + 1);
        vector<int> ind(n + 1);
        for(int i = 0; i < relations.size(); ++i) {
            int u = relations[i][0], v = relations[i][1];
            G[u].push_back(v);
            ++ ind[v];
        }

        queue<int> Q;
        vector<int> DP(n + 1);
        for(int i = 1; i <= n; ++i) {
            if(ind[i] == 0) {
                Q.push(i);
                DP[i] = time[i - 1];
            }
        }

        while(!Q.empty()) {
            int cur = Q.front(); Q.pop();
            for(int nxt : G[cur]) {
                DP[nxt] = max(DP[nxt], DP[cur] + time[nxt - 1]);
                if(--ind[nxt] == 0) Q.push(nxt);
            }
        }
        return *max_element(DP.begin(), DP.end());
    }
};

/* Solution Description
*/

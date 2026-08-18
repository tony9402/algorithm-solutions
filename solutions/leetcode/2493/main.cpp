// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/submissions/1526050397
class Solution {
public:
    int magnificentSets(int N, vector<vector<int>>& edges) {
        vector<vector<int>> G(N);
        for(const auto &e: edges) {
            G[e[0] - 1].push_back(e[1] - 1);
            G[e[1] - 1].push_back(e[0] - 1);
        }
        vector<int> D(N);
        for(int i = 0; i < N; ++i) {
            queue<int> Q; Q.push(i);
            vector<int> dist(N); dist[i] = 1;
            int mx = 1, root = i;
            while(!Q.empty()) {
                int cur = Q.front(); Q.pop();
                root = min(root, cur);
                for(const int &nxt: G[cur]) {
                    if(dist[nxt] == 0) {
                        dist[nxt] = dist[cur] + 1;
                        mx = max(mx, dist[nxt]);
                        Q.push(nxt);
                    }
                    else if(abs(dist[nxt] - dist[cur]) != 1) return -1;
                }
            }
            D[root] = max(D[root], mx);
        }
        return accumulate(D.begin(), D.end(), 0);
    }
};

/* Solution Description
*/

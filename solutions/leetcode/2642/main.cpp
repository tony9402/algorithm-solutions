// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/design-graph-with-shortest-path-calculator/submissions/1096428721
class Graph {
public:
    vector<vector<pair<int, int>>> G;
    Graph(int n, vector<vector<int>>& edges) {
        G.resize(n);
        for(int i = 0; i < (int)edges.size(); ++i) {
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            G[u].emplace_back(v, w);
        }
    }

    void addEdge(vector<int> edge) {
        int u = edge[0], v = edge[1], w = edge[2];
        G[u].emplace_back(v, w);
    }

    int shortestPath(int node1, int node2) {
        static const int INF = 0x3f3f3f3f;
        vector<int> dist(G.size(), INF);
        priority_queue<pair<int, int>> pq;
        pq.emplace(dist[node1] = 0, node1);
        while(!pq.empty()) {
            auto [d, cur] = pq.top(); pq.pop();
            if(dist[cur] != -d) continue;
            for(auto [nxt, w] : G[cur]) {
                if(dist[nxt] > dist[cur] + w) {
                    dist[nxt] = dist[cur] + w;
                    pq.emplace(-dist[nxt], nxt);
                }
            }
        }
        return dist[node2] == INF ? -1 : dist[node2];
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */

/* Solution Description
*/

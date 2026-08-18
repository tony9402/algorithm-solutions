// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-cost-to-convert-string-i/submissions/1900381136
class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        int K = 26;
        const int INF = 0x3f3f3f3f;
        vector<vector<int>> dist(K, vector<int>(K, INF));
        for(int i = 0; i < K; ++i)  dist[i][i] = 0;
        int M = (int)original.size();
        for(int i = 0; i < M; ++i) {
            int &ret = dist[original[i] - 'a'][changed[i] - 'a'];
            ret = min(ret, cost[i]);
        }
        for(int k = 0; k < K; ++k) {
            for(int i = 0; i < K; ++i) {
                for(int j = 0; j < K; ++j) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        long long ans = 0;
        int N = (int)source.size();
        for(int i = 0; i < N; ++i) {
            int a = source[i] - 'a', b = target[i] - 'a';
            if(dist[a][b] == INF) return -1;
            ans += dist[a][b];
        }
        return ans;
    }
};

/* Solution Description
*/

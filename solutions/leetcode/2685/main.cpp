// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/count-the-number-of-complete-components/submissions/2064921755
class Solution {
public:
    int countCompleteComponents(int N, vector<vector<int>>& edges) {
        // uf로 묶고 간선 개수 파악
        vector<int> uf(N, -1);
        vector<int> cnt(N, 0), cnt2(N, 1);
        function<int(int)> find = [&](int x) -> int {
            return uf[x] < 0 ? x : uf[x] = find(uf[x]);
        };
        function<bool(int, int)> merge = [&](int u, int v) -> bool {
            u = find(u); v = find(v);
            ++cnt[u];
            if(u == v) return false;
            uf[v] = u;
            cnt[u] += cnt[v];
            cnt[v] = 0;
            cnt2[u] += cnt2[v];
            cnt2[v] = 0;
            return true;
        };
        int M = (int)edges.size();
        for(int i = 0; i < M; ++i) {
            int u = edges[i][0], v = edges[i][1];
            merge(u, v);
        }
        int ans = 0;
        for(int i = 0; i < N; ++i) {
            int x = find(i);
            if(cnt2[x] == 0) continue;
            int c = cnt2[x];
            ans += (c * (c - 1) / 2 == cnt[x]);
            cnt[x] = cnt2[x] = 0;
        }
        return ans;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/submissions/2064937866
class Solution {
public:
    vector<int> pathExistenceQueries(int N, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {

        vector<int> idx(N);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int u, int v) -> bool {
            return nums[u] < nums[v];
        });

        vector<int> ridx(N);
        for(int i = 0; i < N; ++i) {
            ridx[idx[i]] = i;
        }

        const int D = 18;
        vector<vector<int>> par(D, vector<int>(N));

        for(int i = 0, r = 0; i < N; ++i) {
            r = max(r, i);
            while(r + 1 < N && nums[idx[r + 1]] - nums[idx[i]] <= maxDiff) ++ r;
            par[0][i] = r;
            // 이거는 새로운 인덱스로 해야하니깐 그냥 r이 맞고
        }

        for(int i = 1; i < D; ++i) {
            for(int j = 0; j < N; ++j) {
                par[i][j] = par[i - 1][par[i - 1][j]];
            }
        }

        int Q = (int)queries.size();
        vector<int> answer(Q, -1);
        for(int i = 0; i < Q; ++i) {
            int u = queries[i][0], v = queries[i][1];
            u = ridx[u]; v = ridx[v];
            if(u > v) swap(u, v);
            if(u == v) {
                answer[i] = 0;
                continue;
            }
            int res = 0;
            for(int j = D - 1; j >= 0; --j) {
                if(par[j][u] < v) {
                    u = par[j][u];
                    res |= 1 << j;
                }
            }
            answer[i] = (par[0][u] >= v ? res + 1 : -1);
        }
        return answer;
    }
};

/*
1, 8, 3, 4, 2
nums를 기준으로 정렬하고

0 4 2 3 1
1 2 3 4 8

위 기준에서 한번에 갈 수 있는 가장 오른쪽 기록하면
binary lifting으로 몇 번 이동해야하는지 알 수 있을 듯?


*/

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/course-schedule-iv/submissions/1522188389
class Solution {
public:
    vector<bool> checkIfPrerequisite(int N, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<int>> DP(N, vector<int>(N));
        for(int i = 0; i < prerequisites.size(); ++i) {
            int u = prerequisites[i][0];
            int v = prerequisites[i][1];
            DP[u][v] = 1;
        }
        for(int k = 0; k < N; ++k) {
            for(int i = 0; i < N; ++i) {
                for(int j = 0; j < N; ++j) {
                    DP[i][j] |= DP[i][k] & DP[k][j];
                }
            }
        }
        vector<bool> answer(queries.size());
        for(int i = 0; i < queries.size(); ++i) {
            int u = queries[i][0];
            int v = queries[i][1];
            answer[i] = bool(DP[u][v]);
        }
        return answer;
    }
};

/* Solution Description
*/

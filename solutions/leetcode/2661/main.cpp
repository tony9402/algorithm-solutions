// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/first-completely-painted-row-or-column/submissions/1514183017
class Solution {
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        int N = (int)mat.size();
        int M = (int)mat[0].size();
        vector<int> chk_row(M), chk_col(N);
        vector<pair<int, int>> rindex(arr.size() + 1);
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                rindex[mat[i][j]] = make_pair(i, j);
            }
        }
        int answer = -1;
        for(const int &value: arr) {
            auto [y, x] = rindex[value];
            ++ answer;
            if(++ chk_row[x] == N) break;
            if(++ chk_col[y] == M) break;
        }
        return answer;
    }
};

/* Solution Description
*/

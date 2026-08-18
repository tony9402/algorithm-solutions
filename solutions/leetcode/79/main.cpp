// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/word-search/submissions/1222037675
class Solution {
public:
    const int dy[4] = {-1, 1, 0, 0};
    const int dx[4] = {0, 0, -1, 1};
    bool exist(vector<vector<char>>& board, string word) {
        int N = (int)board.size(), M = (int)board[0].size();
        vector<vector<int>> used(N, vector<int>(M));

        function<bool(int, int, int)> go = [&](int y, int x, int d) -> bool {
            if(d + 1 == word.size()) return true;
            used[y][x] = 1;
            bool flag = false;
            for(int k = 0; !flag && k < 4; ++k) {
                int qy = y + dy[k], qx = x + dx[k];
                if(0 > qy || qy >= N || 0 > qx || qx >= M) continue;
                if(used[qy][qx]) continue;
                if(board[qy][qx] != word[d + 1]) continue;
                flag |= go(qy, qx, d + 1);
            }
            used[y][x] = 0;
            return flag;
        };
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                if(board[i][j] == word[0]) {
                    if(go(i, j, 0)) return true;
                }
            }
        }
        return false;
    }
};

/* Solution Description
*/

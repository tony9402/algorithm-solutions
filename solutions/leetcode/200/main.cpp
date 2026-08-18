// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/number-of-islands/submissions/327095523
const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,1,-1};
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty())return 0;
        const int h = grid.size(), w = grid[0].size();
        int answer = 0;
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                if(grid[i][j] == '1'){
                    grid[i][j]='0';
                    queue<int> q;
                    q.push(i * w + j);
                    answer++;
                    while(!q.empty()){
                        int now = q.front(); q.pop();
                        int ny = now / w, nx = now % w;
                        for(int k=0;k<4;k++){
                            int qy = ny + dy[k];
                            int qx = nx + dx[k];
                            if(0 > qy || qy >= h || 0 > qx || qx >= w)continue;
                            if(grid[qy][qx] == '1'){
                                q.push(qy * w + qx);
                                grid[qy][qx] = '0';
                            }
                        }
                    }
                }
            }
        }
        return answer;
    }
};

/* Solution Description
*/

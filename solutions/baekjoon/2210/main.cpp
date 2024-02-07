// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/eba4fca13cfe4f2e8f5a0100db53ff7d
#include<bits/stdc++.h>

using namespace std;

const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};
const int N = 5;
int arr[5][5];
bool check[1000000];

void dfs(int y, int x, int cnt, int digit) {
    if(cnt == 6) {
        check[digit] = true;
        return;
    }

    for(int k = 0; k < 4; ++k) {
        int ny = y + dy[k];
        int nx = x + dx[k];
        if(0 > ny || ny >= N || 0 > nx || nx >= N) continue;
        dfs(ny, nx, cnt + 1, digit * 10 + arr[ny][nx]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> arr[i][j];
        }
    }

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            dfs(i, j, 1, arr[i][j]);
        }
    }

    int ans = 0;
    for(int i = 0; i < 1000000; ++i) {
        if(check[i]) ++ans;
    }
    cout << ans;

    return 0;
}

/* Solution Description
재귀를 이용한 완전탐색을 잘 돌리면 됨.  
최대 길이가 6인 수만 나오기 때문에 배열로 체크해도 됨.  
*/
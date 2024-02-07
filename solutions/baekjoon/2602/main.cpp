// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/c45cc59eb3d94679b794ca568fbd7a5a
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string S, bridge[2]; cin >> S >> bridge[0] >> bridge[1];
    int N = (int)bridge[0].size();
    int K = (int)S.size();

    // DP[2][N][K]
    vector<vector<vector<int>>> DP(2, vector<vector<int>>(N + 1, vector<int>(K + 1)));

    DP[0][0][0] = DP[1][0][0] = 1;
    for(int i = 1; i <= N; ++i) {
        for(int k = 0; k < 2; ++k) {
            char ch = bridge[k][i - 1];
            for(int l = 1; l <= K; ++l) {
                if(S[l - 1] != ch) continue;
                for(int j = 0; j < i; ++j) {
                    DP[k][i][l] += DP[1 - k][j][l - 1];
                }
            }
        }
    }

    int ans = 0;
    for(int i = 1; i <= N; ++i) {
        ans += DP[0][i][K] + DP[1][i][K];
    }
    cout << ans;
    
    return 0;
}

/* Solution Description
DP[2][N][K]: 
- DP[0][*][*]는 악마의 돌다리를 밟았을 경우, DP[1][*][*]는 천사의 돌다리를 밟았을 경우를 의미.
- N번째 돌다리를 밟았고 현재 위치한 알파벳이 두루마리에 적힌 문자열 중에 하나라면 그 알파벳까지 밟은 경우의 수 
- 주의할 점: 두루마리에 적힌 문자열에서 중복된 문자가 존재할 수 있음.

DP[0][0][0] = DP[1][0][0] = 1 (기저 값)  
`DP[t][i][j] = ∑DP[1 - t][0...i-1][j - 1]`  
시간복잡도: O(N^2K)

Quiz. 여기서 어떻게하면 시간복잡도 O(N^2K)보다 빠르게 할 수 있을까요?
*/
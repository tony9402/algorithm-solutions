// Authored by : tony9402
// Co-authored by : -
// Link : http://boj.kr/2707cccd8fff49c5a12b16f3aaa136ae
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    vector<long long> DP(5);
    string S; cin >> S;
    string K = "DKSH";
    DP[0] = 1;
    for(int i = 0; i < N; ++i) {
        int idx = -1;
        for(int j = 0; j < 4; ++j) {
            if(K[j] == S[i]) {
                idx = j + 1;
                break;
            }
        }
        if(idx != -1) DP[idx] += DP[idx - 1];
    }
    cout << DP[4];

    return 0;
}

/* Solution Description
1번 서브태스크:
완전탐색 O(N^4)  
솔루션 코드(Java): http://boj.kr/20dae18c53344637804b3a27d070bce9  

2번 서브태스크:  
O(N^2)  
DP[i][j]: i번째 알파벳이 "DKSH" 중 j번째 알파벳까지 만드는 경우의 수  
DP[0][0] = 1 => ""를 만드는 경우의 수 (기저 값)  
DP[i][j]: ∑ DP_{0≤k<i}[k][j-1] (i번째 알파벳이 "DKSH" 중에 하나인 경우에만)  
솔루션 코드(Java): http://boj.kr/efe73e4d06434af09f81e443108179b2  

3번 서브태스크:
O(N)  
DP[0] = 1 => ""를 만드는 경우의 수 (기저 값)  
DP[i]: "DKSH" 중 i번째 알파벳까지 만드는 경우의 수  
현재 값이 "DKSH" 중에 하나이고 i번째 값이라 하면 DP[i] += D[i - 1]  
솔루션 코드(C++): http://boj.kr/2707cccd8fff49c5a12b16f3aaa136ae
*/
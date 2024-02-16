// Authored by : tony9402
// Co-authored by : -
// Link : http://boj.kr/2d393ba2e1374ec1bda95577f550d6e7
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(true) {
        int N; cin >> N;
        if(N == -1) break;
        long long S = 1;
        vector<int> factor;
        for(long long i = 2; i * i <= N; ++i) {
            if(N % i == 0) {
                S += i;
                factor.push_back(i);
                if(i * i != N) {
                    S += N / i;
                    factor.push_back(N / i);
                }
            }
        }

        if(S == N) {
            sort(factor.begin(), factor.end());
            cout << N << " = 1";
            for(int x: factor) cout << " + " << x;
            cout << '\n';
        }
        else {
            cout << N << " is NOT perfect.\n";
        }
    }
    
    return 0;
}

/* Solution Description
테스트케이스 수의 최대 값이 정해져있지 않지만 O(NsqrtN) 시간복잡도의 솔루션은 통과
*/
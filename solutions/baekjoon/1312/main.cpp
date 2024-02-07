// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/f98baead51c347eb9f67565082701e07
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long A, B, N; cin >> A >> B >> N;
    A %= B;

    int ans = 0;
    for(int i = 0; i < N; ++i) {
        A *= 10;
        ans = A / B;
        A %= B;
    }
    cout << ans;

    return 0;
}

/* Solution Description
A를 B로 나눈 나머지를 계속 유지해야함.  
N번동안 A에 10을 곱하고 B로 나누는 과정을 통해 N번째 숫자를 구할 수 있음.  
*/
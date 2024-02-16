// Authored by : tony9402
// Co-authored by : -
// Link : http://boj.kr/d1c085db2c784030a0ea6e6c3b0b248f
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    int mn = INT_MAX, ans = 0;
    for(int i = 0; i < N; ++i) {
        int x; cin >> x;
        mn = min(mn, x);
        ans = max(ans, x - mn);
        cout << ans << ' ';
    }

    return 0;
}

/* Solution Description
현재까지 나온 값들 중 최솟값만 계속 들고 가면서 현재 값인 x - mn와 이전에 계산했던 최댓값 중 최댓값을 출력하면 되는 문제.
*/
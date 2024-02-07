// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/327c054505c748d68ef1e3c46b855f7a
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int cnt[2] = {0, 0};
    for(int i = 0; i < 3; ++i) {
        int x; cin >> x;
        if(cnt[x % 2] == 0) cnt[x % 2] = x;
        else cnt[x % 2] *= x;
    }
    if(cnt[1] != 0) cout << cnt[1];
    else cout << cnt[0];

    return 0;
}

/* Solution Description
홀수가 하나라도 있다면 홀수들의 곱을 출력하고 없다면 짝수들만 남아있는 경우이므로 짝수들의 곱을 출력하면 된다.
*/
// Authored by : tony9402
// Co-authored by : -
// Link : http://boj.kr/d71c9ab9881a40b08b8854a9a888e74f
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    int ans = 0;
    for(int i = 1; i <= N; ++i) {
        int tmp = i;
        while(tmp) {
            int cur = tmp % 10;
            if(cur != 0 && cur % 3 == 0) ++ ans;
            tmp /= 10;
        }
    }
    cout << ans;
    
    return 0;
}

/* Solution Description
주어진대로 구현하면 되는 문제.
*/
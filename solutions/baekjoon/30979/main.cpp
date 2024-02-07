// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/23eecf0ad4d34516bf8df6de7b8a64ee
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T; cin >> T;
    int N; cin >> N;
    int S = 0;
    for(int i = 0; i < N; ++i) {
        int x; cin >> x;
        S += x;
    }
    if(S >= T) cout << "Padaeng_i Happy";
    else cout << "Padaeng_i Cry";

    return 0;
}

/* Solution Description
주어진 N개의 합이 T보다 크거나 같은지 확인하면 되는 문제
*/
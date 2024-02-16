// Authored by : tony9402
// Co-authored by : -
// Link : http://boj.kr/6a8e34073dbb48c7899429e8bbd8c8d1
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    const int MAX = 130000;
    vector<int> cnt(MAX + 1);

    auto convert = [&](const string &S) -> int {
        int y = stoi(S.substr(0, 4));
        int m = stoi(S.substr(5, 2));
        return y * 12 + m - 1;
    };

    int N; cin >> N;
    for(int i = 0; i < N; ++i) {
        string u, v; cin >> u >> v;
        cnt[convert(u)] ++;
        cnt[convert(v) + 1] --;
    }
    int mx = 0, ans = 0;
    for(int i = 1; i <= MAX; ++i) {
        cnt[i] += cnt[i - 1];
        if(cnt[i] > mx) {
            mx = cnt[i];
            ans = i;
        }
    }
    int y = ans / 12, m = ans % 12 + 1;
    printf("%04d-%02d", y, m);

    return 0;
}

/* Solution Description
2000년 1월부터 9999년 12월까지를 수로 바꾼 후 스위핑을 하면 된다.
*/
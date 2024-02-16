// Authored by : tony9402
// Co-authored by : -
// Link : http://boj.kr/0d27b72bdd8d4832b2dfdca3f71105df
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    vector<int> V(N);
    for(int i = 0; i < N; ++i) {
        cin >> V[i];
    }
    sort(V.begin(), V.end());
    vector<int> used(N);
    int pre = 0, ans = 0;
    for(int i = 0; i < N; ++i) {
        if(pre < V[i]) {
            used[i] = 1;
            pre = V[i];
            ++ans;
        }
    }
    pre = 1001;
    for(int i = N - 1; i >= 0; --i) {
        if(pre > V[i] && used[i] == 0) {
            pre = V[i];
            ++ ans;
        }
    }
    cout << ans;

    return 0;
}

/* Solution Description
정렬을 하고 작은거부터 큰 값을 보면서 하나씩 선택하고 그리고 큰 값에서부터 다시 작은 값으로 보면서 선택되지 않은 값들을 선택하면 됨.
*/
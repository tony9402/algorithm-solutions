// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/850a62c4f2e14d2d8c3214dbd97398e4
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    vector<pair<int, int>> tree(N + 1);
    for(int i = 1; i <= N; ++i) {
        int a, b, c; cin >> a >> b >> c;
        tree[a] = make_pair(b, c);
    }

    int ans = 2 * (N - 1);
    for(int cur = 1; tree[cur].second != -1; cur = tree[cur].second) {
        -- ans;
    }
    cout << ans;
    
    return 0;
}

/* Solution Description
잘 생각해보면 가장 루트에서 시작하여 가장 오른쪽으로 가는 경로를 제외하고는 2번 이동한다.  
직접 유사 중위 순회를 구현해도 되지만, 잘 관찰을 하면 답은 2 * (N - 1) - (루트에서 시작해서 가장 오른쪽 노드까지 이동하는 횟수)가 되는 것을 알 수 있다.
*/
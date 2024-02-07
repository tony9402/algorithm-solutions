// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/c166de11571b4fd9b979c9f2df110a97
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M; cin >> N >> M;
    vector<int> V(N);
    for(int i = 0; i < N; ++i) cin >> V[i];
    sort(V.begin(), V.end());
    for(int i = 0; i < M; ++i) {
        int l, r; cin >> l >> r;
        int x = lower_bound(V.begin(), V.end(), l) - V.begin();
        int y = lower_bound(V.begin(), V.end(), r + 1) - V.begin();
        cout << y - x << '\n';
    }

    return 0;
}

/* Solution Description
### 주의할 점  
점들이 정렬된 상태로 주어진다는 조건이 없음.  

선분의 시작점과 끝점을 각각 l과 r로 가정한다면 l보다 크거나 같은 값들 중 가장 작은 값의 위치를 구하고  
r보다 큰 값들 중 가장 작은 값의 위치를 구한 후 그 l <= x <= r를 만족하는 값을 세면 되는 문제이다.

매 선분마다 위 조건을 만족하는 점들의 개수를 세는걸 나이브하게 본다면 선분(쿼리)마다 O(N) 시간복잡도가 걸리므로 O(NM)  

하지만, 점들을 정렬하고 이분탐색을 통해 위 조건을 만족하는 점들의 개수를 구할 수 있으므로 O(MlogN)만에 답을 찾을 수 있음.  
근데, 점들은 정렬된 상태로 주어진다는 보장이 업으므로 점들을 정렬하는 시간복잡도도 포함하면 O((N + M)logN).
*/
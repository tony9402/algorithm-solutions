// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/015e042c8e6b4611891355efc3844453
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K; cin >> N >> K;
    vector<int> arr(N), dis(N - 1);
    for(int i = 0; i < N; ++i) cin >> arr[i];
    sort(arr.begin(), arr.end());

    for(int i = 0; i < N - 1; ++i) {
        dis[i] = arr[i + 1] - arr[i];
    }
    sort(dis.begin(), dis.end());

    int ans = 0;
    for(int i = 0; i < N - K; ++i) {
        ans += dis[i];
    }
    cout << ans;

    return 0;
}

/* Solution Description
센서들의 위치를 정렬한 후 사이의 거리들을 계산한다.  
K - 1개의 큰 값들은 집중국을 잘 세우면 커버할 수 있다.  
즉, 거리의 차이에서 N - K개의 합을 더한 값이 집중국을 잘 세웠을 때 길이의 합의 최솟값이다.
*/
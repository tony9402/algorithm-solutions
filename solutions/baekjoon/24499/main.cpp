// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/68d9036a3cd94afd9f2c9d657301fff9
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K; cin >> N >> K;
    vector<int> arr(2 * N + 1);
    vector<int> prefix_sum(2 * N + 1);
    for(int i = 1; i <= N; ++i) {
        cin >> arr[i];
        arr[i + N] = arr[i];
    }
    for(int i = 1; i <= 2 * N; ++i) {
        prefix_sum[i] = prefix_sum[i - 1] + arr[i];
    }

    int ans = 0;
    for(int i = 1; i <= N; ++i) {
        ans = max(ans, prefix_sum[i + K - 1] - prefix_sum[i - 1]);
    }
    cout << ans;

    return 0;
}

/* Solution Description
길이가 고정되어 있는 슬라이딩 윈도우 기법으로 최대값을 구할 수 있음.  
원형으로 되어 있으니깐 하나의 일차원 배열을 두 개를 이어붙어서 보면 쉽게 볼 수 있음.  
그리고 길이가 고정되어 있으므로 누적합을 계산해놓고 연속된 K개의 합이 최대인 값을 찾으면 됨.  
*/
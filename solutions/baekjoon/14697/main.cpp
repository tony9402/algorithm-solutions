// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/76974dc8cc4b4b4a849de1a3f1d91ee3
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int arr[3], N;
    for(int i = 0; i < 3; ++i) cin >> arr[i];
    cin >> N;

    bool answer = false;
    for(int i = 0; arr[0] * i <= N; ++i) {
        for(int j = 0; arr[0] * i + arr[1] * j <= N; ++j) {
            int rem = N - arr[0] * i - arr[1] * j;
            if(rem % arr[2] == 0) answer = true;
        }
    }
    cout << answer;

    return 0;
}

/* Solution Description
가능한 모든 조합을 확인해서 Ax + By + Cz = N을 만족하는 (x, y, z)가 하나라도 있는지 보면 된다.  
시간복잡도는 O(N^2)으로 충분히 돌 수 있다.  
*/
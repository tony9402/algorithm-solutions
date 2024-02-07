// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/2196417f89304eb7a2649144004c38d7
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M; cin >> N >> M;
    vector<long long> V; // 가능한 연주를 bit로 체크해놓고 가지고 있기.
    for(int i = 0; i < N; ++i) {
        string x, y; cin >> x >> y;
        long long available = 0;
        for(char ch: y) {
            available = available << 1 | (ch == 'Y');
        }
        V.emplace_back(available);
    }

    int mx = 0, ans = -1;
    for(int i = 0; i < (1 << N); ++i) {
        long long cur = 0;
        for(int j = 0; j < N; ++j) {
            if(i & (1 << j)) {
                cur |= V[j];
            }
        }
        int cnt = __builtin_popcountll(cur);
        if(cnt > mx) {
            mx = cnt;
            ans = __builtin_popcount(i);
        }
        else if(cnt == mx) {
            ans = min(ans, __builtin_popcount(i));
        }
    }
    cout << ans;

    return 0;
}

/* Solution Description
완전탐색 문제.  
기타의 개수가 10개 밖에 안되니깐 기타를 선택하는 경우의 수는 최대 1024개로 경우의 수가 매우 적은 것을 알 수 있다.  
따라서, 기타를 선택했을 때 연주할 수 있는 곡의 개수가 가장 많은 값을 구하면 되고, 곡의 개수가 가장 많을 땐 선택한 기타의 수가 가장 적은 것을 구하면 된다.  

시간복잡도는 O(NM 2^N) 인데 위처럼 비트 연산을 사용하면 살짝 더 빨라진다. 거의 O(N 2^N)로 봐도 되지만 그냥 나이브하게 구현하는 것 또한 가능하다.  
N의 최대값이 10, M의 최대값이 50이므로 시간복잡도에 값을 넣어 연산횟수를 계산해보면 상당히 값이 작다는 것을 알 수 있다.  
*/
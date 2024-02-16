// Authored by : tony9402
// Co-authored by : -
// Link : http://boj.kr/a603aced05c64ba987d3190c695fef02
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K; cin >> N >> K;
    vector<int> answer(N);
    vector<int> omr(N);
    for(int i = 0; i < N; ++i) cin >> answer[i];
    for(int i = 0; i < N; ++i) cin >> omr[i];

    // 연산 이후 OMR 채점하는 함수
    function<int(const vector<int>&)> cal = [&](const vector<int> &V) -> int {
        int ret = 0;
        for(int i = 0; i < N; ++i) {
            ret += answer[i] == V[i];
        }
        return ret;
    };
    
    function<vector<int>(vector<int>, int)> Push = [&](vector<int> V, int idx) -> vector<int> {
        for(int i = N - 1; i > idx; --i) {
            V[i] = V[i - 1];
        }
        V[idx] = -1;
        return V;
    };
    function<vector<int>(vector<int>, int)> Pull = [&](vector<int> V, int idx) -> vector<int> {
        for(int i = idx; i < N - 1; ++i) {
            V[i] = V[i + 1];
        }
        V[N - 1] = -1;
        return V;
    };

    int ans = 0;
    function<void(int, vector<int>)> go = [&](int cnt, vector<int> V) -> void {
        ans = max(ans, cal(V));
        if(cnt == K) return; // 최대 K번 사용할 수 있는 조건 주의

        // 모든 곳에서 밀거나 당기거나 하면 됨.
        // 밀거나 당기거나 하는 연산은 같은 곳에서 두 번 이상 사용할 수도 있음
        for(int i = 0; i < N; ++i) {
            go(cnt + 1, Push(V, i));
            go(cnt + 1, Pull(V, i));
        }
    };
    go(0, omr);
    cout << ans;

    return 0;
}

/* Solution Description
N이 작아 완전탐색이 가능하다.  
근데 한 지점에서 당기기 또는 밀기를 한 번 "이상"할 수 있다는 것에 주의해야한다.  
*/
// Authored by : tony9402
// Co-authored by : -
// Link : http://boj.kr/9471affea01c478683f7d4b2b1a63c04
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    vector<pair<string, int>> V;
    for(int i = 0; i < N; ++i) {
        string u, v; cin >> u >> v;
        V.emplace_back(u, 1); // 구간의 시작
        V.emplace_back(v, 2); // 구간의 끝
    }
    sort(V.begin(), V.end());

    int cnt = 0, mx = 0;
    string ans = "";
    for(auto [date, type]: V) {
        if(type == 1) { 
            if(++ cnt > mx) {
                mx = cnt;
                ans = date;
            }
        }
        else {
            -- cnt;
        }
    }
    cout << ans;

    return 0;
}

/* Solution Description
이런 일정한 길이의 요일(ex. YYYY-MM)은 파싱을 하지 않고 문자열 비교로만 해도 충분하다.
*/
// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/2ddf5f20f83c4c4e9cf3f2b415202e4b
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    map<string, int> mp;
    string ans;
    int mx = 0;
    for(int i = 0; i < N; ++i) {
        string S; cin >> S;
        int x = ++mp[S];
        if(x > mx) {
            mx = x;
            ans = S;
        }
        else if(x == mx) {
            ans = min(ans, S);
        }
    }
    cout << ans;

    return 0;
}

/* Solution Description
std::map을 이용해서 문자열이 몇 번 나왔는지 개수를 세면서 가장 많이 등장한 문자열을 찾으면 됨.  
가장 많이 등장한 문자열이 여러가지일 경우는 사전순으로 가장 먼저 오는 문자열을 찾아야한다는걸 놓치면 안됨.
*/
// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/9a6e490b384645388ae1aaefc4c04e8f
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= i; ++j) {
            cout << "*";
        }
        cout << "\n";
    }
    
    return 0;
}

/* Solution Description
i는 1부터 N까지 j는 1부터 i까지 중첩 반복문으로 풀면 되는 문제.
*/
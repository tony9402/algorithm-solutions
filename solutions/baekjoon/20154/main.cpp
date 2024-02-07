// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/1883f3f8eb834619b8a1d4315ec5dd1b
#include<bits/stdc++.h>

using namespace std;

const int cnt[] = {3,2,1,2,3,3,3,3,1,1,3,1,3,3,1,2,2,2,1,2,1,1,2,2,2,1};
int arr[1000001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string S; cin >> S;
    for(int i = 0; i < S.size(); ++i) {
        arr[i] = cnt[S[i] - 'A'];
    }

    int N = S.size();
    while(N != 1) {
        for(int i = 1; i < N; ++i) {
            arr[i / 2] += arr[i];
            arr[i / 2] %= 10;
            arr[i] = 0;
        }
        N = (N + 1) / 2;
    }
    if(arr[0] % 2 == 0) {
        cout << "You're the winner?";
    }
    else {
        cout << "I'm a winner!";
    }

    return 0;
}

/* Solution Description
주어진 조건대로 잘 구현하면 되는 문제이다.  
위에서 사용한 기법은 추가 메모리 없이 하나의 배열로 계산하는 방법이다.  
*/
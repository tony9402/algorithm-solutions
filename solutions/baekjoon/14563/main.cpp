// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/4e383f17fcfa484cba0207093d4bc175
#include<bits/stdc++.h>

using namespace std;

string is_perfect_number(int x) {
    int ret = 0;
    for(int i = 1; i < x; ++i) {
        if(x % i == 0) {
            ret += i;
        }
    }

    if(x == ret) return "Perfect";
    else if(x < ret) return "Abundant";
    else return "Deficient";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T; cin >> T;
    for(int i = 0; i < T; ++i) {
        int x; cin >> x;
        cout << is_perfect_number(x) << '\n';
    }

    return 0;
}

/* Solution Description
1부터 x - 1까지 보면서 x의 약수들을 찾고 그 합이 x와 비교하여 답을 출력하면 된다.
시간복잡도 : O(TN) => 약 10^7이므로 1초 안에 돌아갈 수 있다.
*/
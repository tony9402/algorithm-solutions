// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/99720f2ec5754685be4c6b0a3226574d
#include<bits/stdc++.h>

using namespace std;

set<pair<int, int>> problemList;
unordered_map<int, int> problemInfo;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    for(int i=0;i<N;i++){
        int problem, level; cin >> problem >> level;
        problemList.insert(pair<int, int>(level, problem));
        problemInfo[problem] = level;
    }

    int M; cin >> M;
    for(int i=0;i<M;i++){
        string cmd; cin >> cmd;
        if(cmd == "recommend") {
            int x; cin >> x;
            if(x > 0) {
                cout << problemList.rbegin()->second << '\n';
            }
            else {
                cout << problemList.begin()->second << '\n';
            }
        }
        else if(cmd == "solved") {
            int problem; cin >> problem;
            int level = problemInfo[problem];
            problemList.erase(pair<int, int>(level, problem));
            problemInfo.erase(problem);
        }
        else if(cmd == "add") {
            int problem, level; cin >> problem >> level;
            problemList.insert(pair<int, int>(level, problem));
            problemInfo[problem] = level;
        }
    }

    return 0;
}

/* Solution Description
난이도 L과 문제번호 P를 (L, P) 쌍으로 두 개의 heap(힙, 우선순위 큐)로 관리하면 편리하게 최대, 최소를 빠르게 구할 수 있다.
*/
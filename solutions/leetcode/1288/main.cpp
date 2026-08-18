// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/remove-covered-intervals/submissions/2064955141
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int N = 100001;
        vector<int> tree(N + 1);

        function<void(int, int)> update = [&](int x, int delta) -> void {
            for(int i = x; i <= N; i += i & -i) {
                tree[i] += delta;
            }
        };
        function<int(int)> query = [&](int x) -> int {
            int ret = 0;
            for(int i = x; i > 0; i -= i & -i) {
                ret += tree[i];
            }
            return ret;
        };

        int M = (int)intervals.size();
        vector<pair<int, int>> V;
        for(int i = 0; i < M; ++i) {
            int l = intervals[i][0] + 1, r = intervals[i][1] + 1;
            V.emplace_back(l, 1);
            V.emplace_back(r, -l);
        }
        sort(V.begin(), V.end());

        int ans = 0;
        for(auto [x, t]: V) {
            if(t == 1) {
                update(x, 1);
            }
            else {
                int chk = query(-t);
                if(chk == 1) ++ ans;
                update(-t, -1);
            }
        }
        return ans;
    }
};

/*
이거는 L 넣고 R이 온 순간에 L 이하에 있는 값들이 살아있다면 covered 되는 경우
그렇다면 이거는 음 세그를 쓰는게 나을듯한데
l과 r 타입 구분은 0 1 로 해도 되긴 하는데 r일땐 l 값을 알고 있어야 함.

그니깐 r이 나온 시점에 그 l보다 작거나 같고
*/

/* Solution Description
*/

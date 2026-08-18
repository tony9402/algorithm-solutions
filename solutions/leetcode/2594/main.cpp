// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-time-to-repair-cars/submissions/1575626826
class Solution {
public:
    long long repairCars(vector<int>& ranks, int cars) {
        long long l = 1, r = 1e15;
        int N = (int)ranks.size();
        while(l <= r) {
            long long mid = (l + r) / 2;
            long long cnt = 0;
            for(int i = 0; i < N; ++i) {
                long long x = sqrtl(mid / ranks[i]);
                cnt += x;
            }
            if(cnt >= cars) r = mid - 1;
            else l = mid + 1;
        }
        return l;
    }
};

/* Solution Description
*/

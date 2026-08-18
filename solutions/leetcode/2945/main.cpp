// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-maximum-non-decreasing-array-length/submissions/1111511185
const static auto initialize = [] { std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr); return nullptr; }();

class Solution {
using i32 = int;
using i64 = long long;
template<typename T> using Vec = vector<T>;

public:
    int findMaximumLength(vector<int>& nums) {
        i32 N = (i32)nums.size();
        Vec<i64> presum(N + 1, 0);
        for(i32 i = 0; i < N; ++i) {
            presum[i + 1] = presum[i] + nums[i];
        }

        Vec<i64> DP(N + 1);
        Vec<i32> len(N + 1);
        deque<pair<i64, i32>> dq; dq.emplace_back(0, 0);
        for(i32 i = 1; i <= N; ++i) {
            i32 l = 0, r = (i32)dq.size() - 1;
            while(l <= r) {
                i32 mid = (l + r) / 2;
                if(dq[mid].first <= presum[i]) l = mid + 1;
                else r = mid - 1;
            }
            i32 idx = dq[r].second;
            len[i] = len[idx] + 1;
            DP[i] = presum[i] - presum[idx];
            while(!dq.empty() && dq.back().first >= DP[i] + presum[i]) dq.pop_back();
            dq.emplace_back(DP[i] + presum[i], i);
        }

        return len[N];
    }
};

/* Solution Description
*/

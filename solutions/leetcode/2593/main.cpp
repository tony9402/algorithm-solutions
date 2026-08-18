// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/submissions/1477832401
class Solution {
public:
    long long findScore(vector<int>& nums) {
        int N = (int)nums.size();
        vector<int> used(N);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for(int i = 0; i < N; ++i) pq.emplace(nums[i], i);
        long long ans = 0;
        while(!pq.empty()) {
            auto [a, b] = pq.top(); pq.pop();
            if(used[b]) continue;
            for(int k = -1; k <= 1; ++k) {
                int idx = b + k;
                if(0 <= idx && idx < N) used[idx] = 1;
            }
            ans += a;
        }
        return ans;
    }
};

/* Solution Description
*/

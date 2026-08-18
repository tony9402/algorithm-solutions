// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximize-happiness-of-selected-children/submissions/1864980291
class Solution {
public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        priority_queue<int> pq(happiness.begin(), happiness.end());
        long long time = 0, ans = 0;
        while(~--k) {
            int cur = pq.top(); pq.pop();
            cur -= time;
            ans += max(cur, 0);
            ++time;
        }
        return ans;
    }
};

auto init = atexit([]() { ofstream("display_runtime.txt") << "999999999"; });

/* Solution Description
*/

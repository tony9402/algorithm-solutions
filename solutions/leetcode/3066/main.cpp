// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-ii/submissions/1541827040
class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        priority_queue<long long, vector<long long>, greater<>> pq(nums.begin(), nums.end());
        int ans = 0;
        while(pq.top() < k) {
            ++ ans;
            long long a = pq.top(); pq.pop();
            long long b = pq.top(); pq.pop();
            pq.push(min(a, b) * 2 + max(a, b));
        }
        return ans;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimize-deviation-in-array/submissions/1229165695
class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        priority_queue<int> pq;
        int ans = INT_MAX, mn = INT_MAX;
        for(int &x: nums) {
            if(x & 1) x <<= 1;
            pq.push(x);
            mn = min(mn, x);
        }
        while(pq.top() % 2 == 0) {
            int x = pq.top(); pq.pop();
            ans = min(ans, x - mn);
            mn = min(mn, x / 2);
            pq.push(x / 2);
        }
        ans = min(ans, pq.top() - mn);
        return ans;
    }
};
const auto init = []() {
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    return 0;
}();

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/sliding-window-maximum/submissions/804167099
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<pair<int, int>> dq;
        vector<int> ans((int)nums.size()-k+1);
        for(int i = 0; i < (int)nums.size(); ++i) {
            while(!dq.empty()&&dq.back().first<nums[i])dq.pop_back();
            dq.emplace_back(nums[i],i);
            while(dq.front().second<=i-k)dq.pop_front();
            if(i + 1 >= k) ans[i-k+1] = dq.front().first;
        }
        return ans;
    }
};

/* Solution Description
*/

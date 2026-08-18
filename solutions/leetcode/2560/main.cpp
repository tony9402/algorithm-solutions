// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/house-robber-iv/submissions/1574240076
class Solution {
public:
    int minCapability(vector<int>& nums, int k) {
        int l = 1, r = *max_element(nums.begin(), nums.end());
        int N = (int)nums.size();
        while(l < r) {
            int mid = (l + r) / 2;
            int cnt = 0;
            for(int i = 0; i < N; ++i) {
                if(nums[i] <= mid) ++ cnt, ++i;
            }
            if(cnt >= k) r = mid;
            else l = mid + 1;
        }
        return l;
    }
};

/* Solution Description
*/

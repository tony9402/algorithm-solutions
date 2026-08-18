// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/count-number-of-bad-pairs/submissions/1536819525
class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        long long ans = 0;
        unordered_map<int, int> mp;
        for(int i = 0; i < nums.size(); ++i) {
            int diff = i - nums[i];
            ans += i - mp[diff];
            ++ mp[diff];
        }
        return ans;
    }
};

/* Solution Description
*/

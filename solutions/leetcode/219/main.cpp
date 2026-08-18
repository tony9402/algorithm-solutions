// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/contains-duplicate-ii/submissions/827117678
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        vector<int> P = nums;
        sort(P.begin(), P.end());
        P.erase(unique(P.begin(), P.end()), P.end());
        vector<int> index(P.size(), INT_MIN / 2);
        int N = (int)nums.size();
        bool flag=false;
        for(int i = 0; i < N; ++i) {
            int idx = lower_bound(P.begin(), P.end(), nums[i]) - P.begin();
            if(i - index[idx] <= k) flag=true;
            index[idx] = i;
        }
        return flag;
    }
};

/* Solution Description
*/

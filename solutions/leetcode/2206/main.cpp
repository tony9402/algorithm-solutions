// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/divide-array-into-equal-pairs/submissions/1576184608
class Solution {
public:
    bool divideArray(vector<int>& nums) {
        int N = (int)nums.size();
        vector<int> cnt(501);
        for(const int &x: nums) ++ cnt[x];
        for(int i = 1; i <= 500; ++i) {
            if(cnt[i] % 2 != 0) return false;
        }
        return true;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/bitwise-xor-of-all-pairings/submissions/1510542165
class Solution {
public:
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
        int ans = 0;
        if(nums2.size() % 2) for(const int &x: nums1) ans ^= x;
        if(nums1.size() % 2) for(const int &x: nums2) ans ^= x;
        return ans;
    }
};

/* Solution Description
*/

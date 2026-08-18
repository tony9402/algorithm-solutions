// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-common-value/submissions/2006820360
class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        int l = 0, r = 0;
        int N = nums1.size(), M = nums2.size();
        while(l < N && r < M) {
            if(nums1[l] == nums2[r]) return nums1[l];
            if(nums1[l] < nums2[r]) ++ l;
            else ++ r;
        }
        return -1;
    }
};

/* Solution Description
*/

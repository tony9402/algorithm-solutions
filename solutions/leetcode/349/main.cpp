// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/intersection-of-two-arrays/submissions/1199218534
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end()); sort(nums2.begin(), nums2.end());
        vector<int> result;
        int pre = -1;
        while(!nums1.empty() && !nums2.empty()) {
            while(!nums1.empty() && nums1.back() == pre) nums1.pop_back();
            while(!nums2.empty() && nums2.back() == pre) nums2.pop_back();
            if(nums1.empty() || nums2.empty()) break;
            if(nums1.back() == nums2.back()) {
                result.push_back(pre = nums1.back());
                nums1.pop_back(); nums2.pop_back();
            }
            else if(nums1.back() < nums2.back())  nums2.pop_back();
            else if(nums1.back() > nums2.back()) nums1.pop_back();
        }
        return result;
    }
};

/* Solution Description
*/

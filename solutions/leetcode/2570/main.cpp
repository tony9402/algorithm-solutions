// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/merge-two-2d-arrays-by-summing-values/submissions/1560224019
class Solution {
public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        vector<vector<int>> answer;
        int N = (int)nums1.size(), M = (int)nums2.size();
        int l = 0, r = 0;
        while(l < N && r < M) {
            if(nums1[l][0] == nums2[r][0]) {
                nums1[l][1] += nums2[r][1];
                answer.push_back(nums1[l]);
                l++;
                r++;
            }
            else if(nums1[l][0] < nums2[r][0])  answer.push_back(nums1[l ++]);
            else answer.push_back(nums2[r++]);
        }
        while(l < N) answer.push_back(nums1[l ++]);
        while(r < M) answer.push_back(nums2[r ++]);
        return answer;
    }
};

/* Solution Description
*/

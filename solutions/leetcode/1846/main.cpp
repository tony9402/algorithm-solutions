// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/submissions/1099261945
class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int N = (int)arr.size();
        int ans = 1;
        for(int i = 1; i < N; ++i) ans = min(ans + 1, arr[i]);
        return ans;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/product-of-array-except-self/submissions/1203981324
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int N = (int)nums.size();
        vector<int> pre(N + 2, 1), suf(N + 2, 1);
        for(int i = 1; i <= N; ++i) pre[i] = pre[i - 1] * nums[i - 1];
        for(int i = N; i >= 1; --i) suf[i] = suf[i + 1] * nums[i - 1];
        vector<int> answer;
        for(int i = 1; i <= N; ++i) answer.push_back(pre[i - 1] * suf[i + 1]);
        return answer;
    }
};

/* Solution Description
*/

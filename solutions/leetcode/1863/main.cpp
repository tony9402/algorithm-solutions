// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/sum-of-all-subset-xor-totals/submissions/1597520188
class Solution {
public:
    int subsetXORSum(vector<int>& nums) {
        int ans = 0, N = (int)nums.size();
        function<void(int, int)> go = [&](int idx, int x) -> void {
            if(idx == N) {
                ans += x;
                return;
            }
            go(idx + 1, x);
            go(idx + 1, x ^ nums[idx]);
        };
        go(0, 0);
        return ans;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/reduction-operations-to-make-the-array-elements-equal/submissions/1101927819
class Solution {
public:
    int reductionOperations(vector<int>& nums) {
        vector<int> V(50001);
        for(int x: nums)++V[x];
        int cnt = 0, ans = 0;
        for(int i = 1; i <= 50000; ++i) {
            if(V[i]) ans += cnt++ * V[i];
        }
        return ans;
    }
};

/* Solution Description
*/

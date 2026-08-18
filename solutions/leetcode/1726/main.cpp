// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/tuple-with-same-product/submissions/1533863256
class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        unordered_map<int, int> mp;
        int N = (int)nums.size();
        for(int i = 0; i < N; ++i) {
            for(int j = i + 1; j < N; ++j) {
                ++ mp[nums[i] * nums[j]];
            }
        }
        int ans = 0;
        for(auto [k, v]: mp) ans += 4 * v * (v - 1);
        return ans;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/submissions/1539970906
class Solution {
public:
    int maximumSum(vector<int>& nums) {
        vector<pair<int, int>> V(82, make_pair(-1, -1));
        int ans = -1;
        for(int x: nums) {
            int ret = 0, tmp = x;
            while(tmp > 0) {
                ret += tmp % 10;
                tmp /= 10;
            }
            if(V[ret].first < x) {
                V[ret].second = V[ret].first;
                V[ret].first = x;
            }
            else if(V[ret].second < x)  V[ret].second = x;
            if(V[ret].first != -1 && V[ret].second != -1) ans = max(ans, V[ret].first + V[ret].second);
        }
        return ans;
    }
};

/* Solution Description
*/

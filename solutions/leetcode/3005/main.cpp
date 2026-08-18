// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/count-elements-with-maximum-frequency/submissions/1197289332
class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        int mx = 0, mx_cnt = 0;
        int cnt[101]{};
        for(int x: nums) {
            if(mx < ++cnt[x]) {
                mx = cnt[x];
                mx_cnt = 1;
            }
            else if(mx == cnt[x]) ++ mx_cnt;
        }
        return mx_cnt * mx;
    }
};

/* Solution Description
*/

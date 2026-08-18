// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/count-days-without-meetings/submissions/1584963163
class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        map<int,int> mp;
        for(int i = 0; i < meetings.size(); ++i) {
            int u = meetings[i][0], v = meetings[i][1];
            mp[u]++; mp[v+1]--;
        }
        int res = 0, sum = 0, pre = -1;
        for(const auto &[u, v]: mp) {
            if(v > 0 && sum == 0) pre = u;
            sum += v;
            if(sum == 0) res += u - pre, pre = u;
        }
        return days - res;
    }
};

/* Solution Description
*/

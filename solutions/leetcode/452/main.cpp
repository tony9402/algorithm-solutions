// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/submissions/1207339103
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [&](const vector<int> &a, const vector<int> &b) -> bool {
            if(a[1] != b[1]) return a[1] < b[1];
            return a[0] < b[0];
        });
        int ans = 1, N = (int)points.size();
        int pre = points[0][1];
        for(int i = 1; i < N; ++i) {
            if(pre < points[i][0]) {
                ++ ans;
                pre = points[i][1];
            }
        }
        return ans;
    }
};

/* Solution Description
*/

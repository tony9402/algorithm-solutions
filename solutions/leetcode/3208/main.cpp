// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/alternating-groups-ii/submissions/1567988429
class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        for(int i = 0; i < k - 1; ++i) colors.push_back(colors[i]);

        int N = (int)colors.size();
        int ans = 0, l = 0, r = 1;
        while(r < N) {
            if(colors[r] == colors[r - 1]) {
                l = r++; continue;
            }
            ++ r;
            if(r - l < k) continue;
            ++ ans; ++ l;
        }
        return ans;
    }
};

/* Solution Description
*/

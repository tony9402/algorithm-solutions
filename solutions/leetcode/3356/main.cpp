// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/zero-array-transformation-ii/submissions/1571948924
class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int N = (int)nums.size();
        int Q = (int)queries.size();
        int l = 0, r = Q;
        while(l <= r) {
            int mid = (l + r) / 2;
            bool flag = true;
            vector<int> P(N + 1);
            for(int i = 0; i < mid; ++i) {
                int l = queries[i][0], r = queries[i][1];
                P[l] += queries[i][2];
                P[r + 1] -= queries[i][2];
            }
            for(int i = 1; i < N; ++i) P[i] += P[i - 1];
            for(int i = 0; i < N; ++i) flag &= nums[i] <= P[i];
            if(flag) r = mid - 1;
            else l = mid + 1;
        }
        return l > Q ? -1 : l;
    }
};

/* Solution Description
*/

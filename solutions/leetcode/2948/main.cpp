// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/submissions/1524233695
class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int N = (int)nums.size();
        vector<int> idx(N); iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int u, int v) -> bool { return nums[u] < nums[v]; });
        vector<vector<int>> G;
        G.emplace_back(); G.back().push_back(idx[0]);
        for(int i = 1; i < N; ++i) {
            if(nums[idx[i]] - nums[G.back().back()] > limit) G.emplace_back();
            G.back().push_back(idx[i]);
        }
        vector<vector<int>> seq = G;
        vector<int> answer(N);
        for(int i = 0; i < (int)seq.size(); ++i) {
            sort(seq[i].begin(), seq[i].end());
            for(int j = 0; j < (int)seq[i].size(); ++j) answer[seq[i][j]] = nums[G[i][j]];
        }
        return answer;
    }
};

/* Solution Description
*/

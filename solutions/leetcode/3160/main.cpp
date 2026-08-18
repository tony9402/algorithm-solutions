// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-the-number-of-distinct-colors-among-the-balls/submissions/1534462671
class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        vector<int> answer;
        unordered_map<int, int> mp, color;
        for(int i = 0; i < (int)queries.size(); ++i) {
            int u = queries[i][0], v = queries[i][1];
            if(color[u] > 0 && --mp[color[u]] == 0) mp.erase(color[u]);
            color[u] = v;
            ++ mp[v];
            answer.push_back(mp.size());
        }
        return answer;
    }
};

/* Solution Description
*/

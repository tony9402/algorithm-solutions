// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/letter-tile-possibilities/submissions/1545983603
class Solution {
public:

    int numTilePossibilities(string tiles) {
        vector<int> cnt(26);
        for(char ch: tiles) ++ cnt[ch - 'A'];
        int ans = 0;
        vector<int> used(26);
        function<void(int)> dfs = [&](int dep) -> void {
            if(dep > 0) ++ ans;
            if(dep == tiles.size())  return;
            for(int i = 0; i < 26; ++i) {
                if(cnt[i] == 0) continue;
                -- cnt[i];
                dfs(dep + 1);
                ++ cnt[i];
            }
        };
        dfs(0);
        return ans;
    }
};

/* Solution Description
*/

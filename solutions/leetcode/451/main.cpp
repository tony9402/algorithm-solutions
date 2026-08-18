// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/sort-characters-by-frequency/submissions/1169251386
class Solution {
public:
    string frequencySort(string s) {
        vector<pair<int, char>> V;
        vector<int> cnt(255);
        for(char ch: s) ++ cnt[ch];
        for(char ch: s) {
            if(cnt[ch]) V.emplace_back(cnt[ch], ch), cnt[ch] = 0;
        }
        sort(V.begin(), V.end(), greater<>());
        string ans;
        for(int i = 0; i < (int)V.size(); ++i) ans += string(V[i].first, V[i].second);
        return ans;
    }
};

/* Solution Description
*/

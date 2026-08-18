// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/word-subsets/submissions/1503696008
class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        int N = (int)words1.size(), M = (int)words2.size();
        vector<int> cnt(26);
        for(const string &S: words2) {
            vector<int> c(26);
            for(const char &ch: S) {
                ++ c[ch - 'a'];
            }
            for(int i = 0; i < 26; ++i) cnt[i] = max(cnt[i], c[i]);
        }
        vector<string> answer;
        for(const string &S: words1) {
            vector<int> c(26);
            for(const char &ch: S) {
                ++ c[ch - 'a'];
            }
            bool flag = true;
            for(int i = 0; flag && i < 26; ++i) flag &= c[i] >= cnt[i];
            if(flag) answer.push_back(S);
        }
        return answer;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/count-vowel-strings-in-ranges/submissions/1494574069
class Solution {
public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        int N = (int)words.size();
        vector<int> V(N);
        auto chk = [&](char ch) -> bool {
            return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
        };
        for(int i = 0; i < N; ++i) V[i] = chk(words[i][0]) && chk(words[i].back());
        for(int i = 1; i < N; ++i) V[i] += V[i - 1];
        int M = (int)queries.size();
        vector<int> answer(M);
        for(int i = 0; i < M; ++i) {
            int l = queries[i][0] - 1, r = queries[i][1];
            answer[i] = V[r] - (l < 0 ? 0 : V[l]);
        }
        return answer;
    }
};

/* Solution Description
*/

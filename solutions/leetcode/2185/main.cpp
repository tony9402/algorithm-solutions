// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/counting-words-with-a-given-prefix/submissions/1502506454
class Solution {
public:
    int prefixCount(vector<string>& words, string pref) {
        int N = (int)words.size();
        int K = (int)pref.size();
        vector<int> idx(N); iota(idx.begin(), idx.end(), 0);
        for(int i = 0; i < K; ++i) {
            int p = 0;
            for(int j = 0; j < N; ++j) {
                if(words[idx[j]][i] == pref[i]) idx[p ++] = idx[j];
            }
            N = p;
        }
        return N;
    }
};

/* Solution Description
*/

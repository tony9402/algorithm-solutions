// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/count-prefix-and-suffix-pairs-i/submissions/1502499492
class Solution {
public:
    bool isPrefixAndSuffix(const string &a, const string &b) {
        int N = a.size(), M = b.size();
        for(int i = 0; i < N; ++i) {
            if(a[i] != b[i]) return false;
            if(a[N - 1 - i] != b[M - 1 - i]) return false;
        }
        return true;
    }
    int countPrefixSuffixPairs(vector<string>& words) {
        int N = (int)words.size();
        int ans = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = i + 1; j < N; ++j) {
                if(isPrefixAndSuffix(words[i], words[j])) ++ ans;
            }
        }
        return ans;
    }
};

/* Solution Description
*/

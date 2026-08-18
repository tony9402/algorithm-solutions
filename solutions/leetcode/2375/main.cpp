// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/construct-smallest-number-from-di-string/submissions/1547277303
class Solution {
public:
    string smallestNumber(string pattern) {
        int N = (int)pattern.size() + 1;
        vector<int> V(N); iota(V.begin(), V.end(), 1);
        do {
            bool flag = true;
            for(int i = 1; flag && i < N; ++i) {
                char ch = 'D';
                if(V[i - 1] < V[i]) ch = 'I';
                if(pattern[i - 1] != ch) flag = false;
            }
            if(flag) break;
        } while(next_permutation(V.begin(), V.end()));
        string ans = "";
        for(int x: V) ans += to_string(x);
        return ans;
    }
};

/* Solution Description
*/

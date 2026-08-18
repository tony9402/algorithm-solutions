// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/k-th-symbol-in-grammar/submissions/479664935
class Solution {
public:
    int kthGrammar(int N, int K) {
        N = K;
        K = 0;
        while(N){
            int cur = 1;
            while(cur * 2 < N) cur <<= 1;
            N -= cur;
            K ++;
        }
        return ~K & 1;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/submissions/1507923187
class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        long long l = 0, r = 0;
        int N = (int)A.size();
        for(int i = 0; i < N; ++i) {
            l |= 1LL << A[i];
            r |= 1LL << B[i];
            A[i] = __builtin_popcountll(l & r);
        }
        return A;
    }
};

/* Solution Description
*/

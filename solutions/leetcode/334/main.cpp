// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/increasing-triplet-subsequence/submissions/1492989801
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int N = nums.size();
        vector<int> L(N), R(N);
        for(int i = 0; i < N; ++i) {
            if(i == 0) L[i] = nums[i];
            else L[i] = min(L[i - 1], nums[i]);
        }
        for(int i = N - 1; i >= 0; --i) {
            if(i == N - 1) R[i] = nums[i];
            else R[i] = max(R[i + 1], nums[i]);
        }
        for(int i = 1; i < N - 1; ++i) {
            if(L[i - 1] < nums[i] && nums[i] < R[i + 1]) {
                cout << i << ' ';
                return true;
            }
        }
        return false;
    }

};

/* Solution Description
*/

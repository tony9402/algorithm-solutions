// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/partition-array-according-to-given-pivot/submissions/1561430951
class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> L, M, R;
        for(const int &x: nums) {
            if(x < pivot) L.push_back(x);
            else if(x == pivot) M.push_back(x);
            else R.push_back(x);
        }
        for(const int &x: M) L.push_back(x);
        for(const int &x: R) L.push_back(x);
        return L;
    }
};

/* Solution Description
*/

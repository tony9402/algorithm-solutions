// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/move-zeroes/submissions/319666201
#pragma optimize("Ofast")
#pragma optimize("unrolls-loop")

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
        for(vector <int>::iterator it = std::remove(nums.begin(), nums.end(), 0); it != nums.end(); it++)
            *it = 0;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-unique-binary-string/submissions/1550112731
class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        string ans = "";
        for(int i = 0; i < (int)nums.size(); ++i) {
            ans += ('a' - nums[i][i]);
        }
        return ans;
    }
};

/* Solution Description
*/

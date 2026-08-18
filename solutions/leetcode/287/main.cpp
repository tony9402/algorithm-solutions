// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-the-duplicate-number/submissions/1212338462
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow, fast; slow = fast = nums[0];
        do { slow = nums[slow], fast = nums[nums[fast]]; } while(slow != fast);
        slow = nums[0];
        while(slow != fast) slow = nums[slow], fast = nums[fast];
        return slow;
    }
};
int init = [] {
    ios_base::sync_with_stdio(false);  cin.tie(nullptr);
    return 0;
}();

/* Solution Description
*/

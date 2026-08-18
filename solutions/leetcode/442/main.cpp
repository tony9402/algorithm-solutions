// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-all-duplicates-in-an-array/submissions/1213191130
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int N = (int)nums.size();
        vector<int> answer;
        for(int i = 0, cur; i < N; ++i) {
            cur = abs(nums[i]) - 1;
            if(nums[cur] < 0) answer.push_back(cur + 1);
            else nums[cur] = -nums[cur];
        }
        return answer;
    }
};

/* Solution Description
*/

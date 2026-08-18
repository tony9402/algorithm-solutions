// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/distribute-elements-into-two-arrays-i/submissions/1192134082
class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        vector<int> V, W;
        vector<int> answer;
        V.push_back(nums[0]);
        W.push_back(nums[1]);
        for(int i = 2; i < nums.size(); ++i) {
            if(V.back() > W.back()) V.push_back(nums[i]);
            else W.push_back(nums[i]);
        }
        for(int &x: V) answer.push_back(x);
        for(int &x: W) answer.push_back(x);
        return answer;
    }
};

/* Solution Description
*/

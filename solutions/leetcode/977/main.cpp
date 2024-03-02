// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/squares-of-a-sorted-array/submissions/1191057000
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int N = nums.size();
        vector<int> answer(N);
        for(int i = N - 1, l = 0, r = N - 1; i >= 0; --i) {
            if(abs(nums[l]) >= abs(nums[r])) answer[i] = nums[l] * nums[l ++];
            else answer[i] = nums[r] * nums[r --];
        }
        return answer;
    }
}

/* Solution Description
이미 정렬된 배열이므로 양 끝에서부터 제곱이 가장 큰 값으로 뒤에서부터 채워나가면 된다.  

Time Complexity: O(N)
*/
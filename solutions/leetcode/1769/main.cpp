// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/submissions/1499348365
class Solution {
public:
    vector<int> minOperations(string boxes) {
        int N = (int)boxes.size();
        vector<int> V(N + 2);
        int left_cnt = 0, sum = 0;
        vector<int> answer(N);
        for(int i = 1; i <= N; ++i) {
            answer[i - 1] = sum;
            if(boxes[i - 1] == '1') ++ left_cnt;
            sum += left_cnt;
        }
        int right_cnt = 0; sum = 0;
        for(int i = N; i >= 1; --i) {
            answer[i - 1] += sum;
            if(boxes[i - 1] == '1') ++ right_cnt;
            sum += right_cnt;
        }
        return answer;
    }
};

/* Solution Description
*/

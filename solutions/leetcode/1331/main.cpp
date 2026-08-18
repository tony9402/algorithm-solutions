// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/rank-transform-of-an-array/submissions/2064916332
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> V = arr;
        sort(V.begin(), V.end());
        V.erase(unique(V.begin(), V.end()), V.end());

        int N = (int)arr.size();
        vector<int> answer(N);
        for(int i = 0; i < N; ++i) {
            answer[i] = lower_bound(V.begin(), V.end(), arr[i]) - V.begin() + 1;
        }
        return answer;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/submissions/1226671048
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        int N = (int)students.size();
        vector<int> used(N);
        int ret = 0, i = 0;
        for(int x: sandwiches) {
            bool flag = false;
            for(int k = 0; k < N; ++k, i = (i + 1) % N) {
                if(used[i]) continue;
                if(students[i] == x) {
                    flag = true;
                    break;
                }
            }
            if(!flag) break;
            ++ ret;
            used[i] = true;
        }
        return N - ret;
    }
};

/* Solution Description
*/

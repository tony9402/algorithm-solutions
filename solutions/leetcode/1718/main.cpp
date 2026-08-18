// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/submissions/1544887742
class Solution {
public:
    vector<int> constructDistancedSequence(int n) {
        vector<int> answer(n * 2 - 1), used(n + 1);
        function<bool(int)> go = [&](int cnt) -> bool {
            if(cnt == n)  return true;
            int idx = 0;
            while(idx < 2 * n - 1 && answer[idx] != 0) ++ idx;
            for(int i = n; i >= 1; --i) {
                // Check Valid
                if(used[i] || idx + (i > 1 ? i : 0) >= 2 * n - 1) continue;
                bool flag = answer[idx] == 0;
                if(i != 1) flag &= answer[idx + i] == 0;
                if(!flag) continue;

                // Put Item
                answer[idx] = i;
                if(i != 1) answer[idx + i] = i;
                used[i] = 1;

                if(go(cnt + 1)) return true;

                // Revert
                used[i] = 0;
                answer[idx] = 0;
                if(i != 1) answer[idx + i] = 0;
            }
            return false;
        };
        go(0);

        return answer;
    }
};

/* Solution Description
*/

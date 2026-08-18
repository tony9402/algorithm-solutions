// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/task-scheduler/submissions/1208357133
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> cnt(26);
        for(char ch: tasks) ++cnt[ch-'A'];
        sort(cnt.begin(), cnt.end());
        int x = cnt.back() - 1;
        int y = x * n;
        for(int i = 24; i >= 0; --i)  y -= min(x, cnt[i]);
        return tasks.size() + max(0, y);
    }
};

/* Solution Description
*/

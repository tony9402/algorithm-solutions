// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/last-stone-weight/submissions/323580089
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> q;
        for(auto &i: stones)
            q.push(i);
        while(q.size() > 1 ){
            int f = q.top();q.pop();
            int s = q.top();q.pop();
            if(f == s)continue;
            q.push(f - s);
        }
        if(q.empty())return 0;
        else return q.top();
    }
};

/* Solution Description
*/

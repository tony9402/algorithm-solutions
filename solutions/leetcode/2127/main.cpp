// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/submissions/1522207927
class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        int N = (int)favorite.size();
        vector<int> ind(N);
        for(const int &x: favorite) ++ ind[x];
        queue<int> Q;
        for(int i = 0; i < N; ++i)  if(ind[i] == 0) Q.push(i);

        vector<int> dep(N, 1);
        while(!Q.empty()) {
            int cur = Q.front(); Q.pop();
            int nxt = favorite[cur];
            dep[nxt] = max(dep[nxt], dep[cur] + 1);
            if(--ind[nxt] == 0) Q.push(nxt);
        }

        int mx = 0, ans = 0;
        for(int i = 0; i < N; ++i) {
            if(!ind[i]) continue;
            int len = 0, cur = i;
            while(ind[cur]) ind[cur] = 0, ++len, cur = favorite[cur];
            if(len == 2) ans += dep[i] + dep[favorite[i]];
            else mx = max(mx, len);
        }
        ans = max(ans, mx);
        return ans;
    }
};

/* Solution Description
*/

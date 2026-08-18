// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/counting-elements/submissions/321162810
class Solution {
public:
    int countElements(vector<int>& arr) {
        ios::sync_with_stdio(false);cin.tie(0);
        int count[1001] = {0};
        for(auto &i : arr)
            count[i]++;
        int ans = 0;
        for(int i=1;i<=1000;i++){
            if(count[i - 1] == 0 || count[i] == 0)continue;
            ans += count[i-1];
        }
        return ans;
    }
};

/* Solution Description
*/

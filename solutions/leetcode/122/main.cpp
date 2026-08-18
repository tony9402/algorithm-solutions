// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/submissions/320036497
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        ios::sync_with_stdio(false);cin.tie(0);
        int ans=0;
        for(int i=1;i<prices.size();i++){
            if(prices[i] - prices[i-1] >= 0)
                ans += prices[i] - prices[i-1];
        }
        return ans;
    }
};

/* Solution Description
*/

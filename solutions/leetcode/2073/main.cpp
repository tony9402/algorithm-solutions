// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/time-needed-to-buy-tickets/submissions/1227605750
class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        int ret = 0;
        while(tickets[k] > 0) {
            for(int i = 0; i < tickets.size(); ++i) {
                if(tickets[i] > 0) -- tickets[i], ++ret;
                if(i == k && tickets[i] == 0) break;
            }
        }
        return ret;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/reveal-cards-in-increasing-order/submissions/1229368550
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        sort(deck.begin(), deck.end());
        int N = (int)deck.size();
        vector<int> ans(N);
        deque<int> dq(N); iota(dq.begin(), dq.end(), 0);
        for(int i = 0; i < N; ++i) {
            int cur = dq[0]; dq.pop_front();
            ans[cur] = deck[i];
            if(i + 1 != N) dq.push_back(dq.front()), dq.pop_front();
        }
        return ans;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/apple-redistribution-into-boxes/submissions/1199047104
class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        sort(capacity.rbegin(), capacity.rend());
        int S = accumulate(apple.begin(), apple.end(), 0);
        for(int i = 0; i < capacity.size(); ++i) {
            S -= capacity[i];
            if(S <= 0) return i + 1;
        }
        return capacity.size();
    }
};

/* Solution Description
*/

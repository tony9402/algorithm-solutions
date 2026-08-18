// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/custom-sort-string/submissions/1200024942
class Solution {
public:
    string customSortString(string order, string s) {
        vector<int> idx(255, 255);
        for(int i = 0; i < (int)order.size(); ++i) idx[order[i]] = i;
        sort(s.begin(), s.end(), [&](char a, char b) -> bool { return idx[a] < idx[b]; });
        return s;
    }
};

/* Solution Description
*/

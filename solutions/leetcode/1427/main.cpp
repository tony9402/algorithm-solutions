// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/perform-string-shifts/submissions/325071586
class Solution {
public:
    string stringShift(string s, vector<vector<int>>& shift) {
        int start = 0, mod = s.size();
        for(auto i: shift){
            int t = i[1];
            if(i[0] == 0){
                start = (start + t) % mod;
            }
            else{
                start = (start - t + mod) % mod;
            }
        }
        if(start == 0)return s;
        return s.substr(start, mod - start) + s.substr(0, start);
    }
};

/* Solution Description
*/

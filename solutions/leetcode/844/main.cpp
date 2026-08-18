// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/backspace-string-compare/submissions/322196172
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int sidx=0, tidx=0;
        for(int i=0;i<S.size();i++){
            if(S[i] == '#')sidx--;
            else S[sidx++] = S[i];
            if(sidx < 0)sidx = 0;
        }
        for(int i=0;i<T.size();i++){
            if(T[i] == '#')tidx--;
            else T[tidx++] = T[i];
            if(tidx < 0)tidx = 0;
        }
        if(sidx != tidx)return false;
        sidx--;tidx--;
        if(sidx < 0 || tidx < 0)return true;
        while(sidx > 0 && tidx > 0 && S[sidx] == T[tidx])sidx--,tidx--;
        return S[sidx] == T[tidx];
    }
};

/* Solution Description
*/

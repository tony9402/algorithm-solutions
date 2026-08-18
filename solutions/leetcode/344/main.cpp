// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/reverse-string/submissions/259266677
#include<algorithm>

class Solution {
public:
    void reverseString(vector<char>& s) {
        vector<char> other;
        for(int i=s.size()-1;i>=0;i--){
            other.push_back(s[i]);
        }
        s = other;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/largest-number/submissions/1393892109
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [&](int a, int b) -> bool {
            string L = to_string(a) + to_string(b);
            string R = to_string(b) + to_string(a);
            return L > R;
        });
        string S;
        for(int x: nums) S += to_string(x);
        int trim = 0;
        while(trim < S.size() && S[trim] == '0') ++ trim;
        if(trim > 0) S = S.substr(trim - 1);
        return S;
    }
};

/* Solution Description
*/

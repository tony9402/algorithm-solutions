// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/plus-one/submissions/1870746730
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry = 1;
        int N = (int)digits.size();
        for(int i = N - 1; i >= 0; --i) {
            digits[i] += carry;
            carry = digits[i] / 10;
            digits[i] %= 10;
        }
        if(carry) digits.insert(digits.begin(), carry);
        return digits;
    }
};

/* Solution Description
*/

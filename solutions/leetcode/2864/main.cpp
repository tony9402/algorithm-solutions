// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/maximum-odd-binary-number/submissions/1190335975
class Solution {
public:
    string maximumOddBinaryNumber(string s) {
        int k = 0;
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] == '1') swap(s[k ++], s[i]);
        }
        swap(s[k - 1], s.back());
        return s;
    }
};

/* Solution Description
적어도 한 개 이상 '1'이 주어지므로 무조건 홀수를 만들 수 있다.  

홀수이면서 가장 큰 수로 만들기 위해서는 '1'을 하위비트에 배치하고 나머지 '1'들을 가장 상위비트에 몰아넣으면 된다.  
*/
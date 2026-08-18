// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/integer-to-english-words/submissions/1200009933
class Solution {
public:
    string A[4]  = {"", "Thousand", "Million", "Billion"};
    string B[10] = {"", "One","Two","Three","Four","Five","Six","Seven","Eight","Nine"};
    string C[10] = {"Ten", "Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"};
    string D[10] = {"", "", "Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"};
    string numberToWords(int num, int dep = 0) {
        if(num == 0 && dep == 0) return "Zero";
        if(num == 0) return "";
        string ret = "";
        int remain = num % 1000;
        bool flag = remain;
        if(remain >= 100) ret += B[remain / 100] + " Hundred ",  remain %= 100;
        if(remain >= 20) ret += D[remain / 10] + " ", remain %= 10;
        if(remain >= 10) ret += C[remain % 10] + " ", remain = 0;
        if(remain) ret += B[remain] + " ", remain = 0;
        if(flag && dep) ret += A[dep] + " ";
        string result = numberToWords(num / 1000, dep + 1) + ret;
        if(dep == 0) while(!result.empty() && result.back() == ' ') result.pop_back();
        return result;
    }
};

/* Solution Description
*/

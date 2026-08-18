// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-window-substring/submissions/1188574912
class Solution {
public:
    int charToInt(char ch) {
        if('a' <= ch && ch <= 'z') return ch - 'a';
        else return ch - 'A' + 26;
    }
    string minWindow(string s, string t) {
        int cnt[52]{}, target[52]{};
        for(char ch: t) ++ target[charToInt(ch)];
        long long chk = 0, cur = 0;

        int mn = s.size() + 1, start_idx = -1;

        auto isSame = [&]() -> bool {
            for(int i = 0; i < 52; ++i) {
                if(target[i] > 0 && cnt[i] < target[i]) return false;
            }
            return true;
        };

        for(int i = 0, r = -1; i < s.size(); ++i) {
            while(r + 1 < s.size() && !isSame())  ++ cnt[charToInt(s[++ r])];
            if(isSame()) {
                int siz = r - i + 1;
                if(mn > siz)  mn = siz, start_idx = i;
            }
            -- cnt[charToInt(s[i])];
        }
        string ans = "";
        if(start_idx != -1) {
            for(int i = start_idx; i < min<int>(start_idx + mn, s.size()); ++i) {
                ans += s[i];
            }
        }
        return ans;
    }
};

/* Solution Description
*/

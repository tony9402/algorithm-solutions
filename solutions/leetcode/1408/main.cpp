// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/string-matching-in-an-array/submissions/1500285336
class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        sort(words.begin(), words.end(), [&](const string &a, const string &b) -> bool {
            return a.size() < b.size();
        });
        int N = words.size();
        vector<string> answer;
        for(int i = 0; i < N; ++i) {
            for(int j = i + 1; j < N; ++j) {
                if(words[j].find(words[i]) != string::npos) {
                    answer.push_back(words[i]);
                    break;
                }
            }
        }
        return answer;
    }
};

/* Solution Description
*/

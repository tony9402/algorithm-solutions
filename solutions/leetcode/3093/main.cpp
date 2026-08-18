// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/longest-common-suffix-queries/submissions/1212315787
struct Trie {
    struct Node {
        vector<pair<char, Node*>> nxt;
        int idx, len;
        Node():Node(INT_MAX, INT_MAX) { nxt.reserve(26); }
        Node(int idx, int len):idx(idx),len(len) {}
    };

    Node* head;
    Trie() { head = new Node(); }

    void Insert(const string &S, int idx) {
        Node *cur = head;
        int N = (int)S.size();
        if(N < cur->len) cur->len = N, cur->idx = idx;
        for(int i = N - 1; i >= 0; --i) {
            int nxtIdx = (int)cur->nxt.size();
            for(int j = 0; j < (int)cur->nxt.size(); ++j) {
                if(cur->nxt[j].first == S[i]) nxtIdx = j;
            }
            if(nxtIdx == cur->nxt.size()) {
                cur->nxt.resize(cur->nxt.size() + 1);
                cur->nxt[nxtIdx] = make_pair(S[i], new Node(idx, N));
            }
            cur = cur->nxt[nxtIdx].second;
            if(N < cur->len) cur->len = N, cur->idx = idx;
        }
    }
    int Query(const string &S) {
        Node *cur = head;
        int N = (int)S.size();
        for(int i = N - 1; i >= 0; --i) {
            int nxtIdx = (int)cur->nxt.size();
            for(int j = 0; j < (int)cur->nxt.size(); ++j) {
                if(cur->nxt[j].first == S[i]) nxtIdx = j;
            }
            if(nxtIdx == cur->nxt.size()) break;
            cur = cur->nxt[nxtIdx].second;
        }
        return cur->idx;
    }
};

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        Trie trie;
        int idx = 0;
        for(const auto &a: wordsContainer) trie.Insert(a, idx ++);
        vector<int> answer;
        for(const auto &a: wordsQuery)  answer.push_back(trie.Query(a));
        return answer;
    }
};

int init = [] {
    ios_base::sync_with_stdio(false);  cin.tie(nullptr);
    return 0;
}();

/* Solution Description
*/

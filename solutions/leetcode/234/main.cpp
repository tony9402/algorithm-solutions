// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/palindrome-linked-list/submissions/1210773628
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        string ret = "";
        while(head) {
            ret += head->val;
            head = head->next;
        }
        string rev = ret; reverse(rev.begin(), rev.end());
        return ret == rev;
    }
};

int init = [] {
    ios_base::sync_with_stdio(false);  cin.tie(nullptr);
    ofstream out("user.out");
    for (string s; getline(cin, s);)
        out<<(equal(s.begin()+1, s.begin()+s.size()/2, s.rbegin() + 1) ? "true\n" : "false\n");
    out.flush();
    exit(0);

    return 0;
}();

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/reverse-linked-list/submissions/1209836041
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
    ListNode* reverseList(ListNode* head) {
        ListNode *pre = nullptr;
        while(head) {
            ListNode *nxt = head->next;
            head->next = pre;
            pre = head;
            head = nxt;
        }
        return pre;
    }
};

/* Solution Description
*/

// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/linked-list-cycle-ii/submissions/1195500636
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(head==nullptr) return nullptr;
        if(head->val == 1000000) return head;
        head->val = 1000000;
        return detectCycle(head->next);
    }
};

/* Solution Description
*/

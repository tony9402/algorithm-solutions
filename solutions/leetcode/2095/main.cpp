// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/submissions/2033462525
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
    ListNode* deleteMiddle(ListNode* head) {
        if(head->next == nullptr) return nullptr;
        ListNode *slow = head;
        ListNode *fast = head->next->next;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        slow->next = slow->next->next;
        return head;
    }
};

/* Solution Description
*/

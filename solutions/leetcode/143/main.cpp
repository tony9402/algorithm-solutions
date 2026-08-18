// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/reorder-list/submissions/1211735942
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
    void reorderList(ListNode* head) {
        ListNode *slow= head, *fast = head;
        while(fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        if(fast->next) slow = slow->next;
        ListNode *tmp = nullptr;
        while(slow) {
            fast = slow->next;
            slow->next = tmp;
            tmp = slow;
            slow = fast;
        }
        slow = tmp;
        while(head && slow) {
            fast = head->next;
            tmp = slow->next;
            head->next = slow;
            slow->next = fast;
            head = fast;
            slow = tmp;
        }
        if(head && head->next) head->next->next = nullptr;
    }
};
int init = [] {
    ios_base::sync_with_stdio(false);  cin.tie(nullptr);
    return 0;
}();

/* Solution Description
*/

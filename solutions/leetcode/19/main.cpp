// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/remove-nth-node-from-end-of-list/submissions/1192206120
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *pre = head, *cur = head;
        for(int i = 0; i < n && cur; ++i) cur = cur->next;
        if(cur == nullptr) return pre->next;
        while(cur && cur->next) pre = pre->next, cur = cur->next;
        if(pre->next) pre->next = pre->next->next;
        else pre->next = nullptr;
        return head;
    }
};

/* Solution Description
*/

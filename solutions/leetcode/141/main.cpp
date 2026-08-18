// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/linked-list-cycle/submissions/1195498120
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
    bool hasCycle(ListNode *head) {
        if(head==nullptr) return false;
        if(head->val == 1000000) return true;
        head->val = 1000000;
        return hasCycle(head->next);
    }
};

/* Solution Description
*/

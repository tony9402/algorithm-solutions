// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/submissions/1201038360
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
    ListNode* removeZeroSumSublists(ListNode* head) {
        unordered_map<int, ListNode*> mp;
        int S = 0;
        ListNode *dummy = new ListNode(0, head);
        ListNode *cur = dummy;
        while(cur) {
            S += cur->val;
            mp[S] = cur;
            cur = cur->next;
        }
        cur = dummy; S = 0;
        while(cur) {
            S += cur->val;
            cur->next = mp[S]->next;
            cur = cur->next;
        }
        return dummy->next;
    }
};

/* Solution Description
*/

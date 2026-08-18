// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/merge-in-between-linked-lists/submissions/1209266601
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
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode *cur = list1;
        int idx = 0;
        while(idx + 1 < a) cur = cur->next, idx++;
        ListNode *cur2 = cur;
        while(idx <= b) cur2 = cur2->next, idx++;
        ListNode *last = list2;
        while(last && last->next) last = last->next;
        cur->next = list2;
        last->next = cur2;
        return list1;
    }
};

/* Solution Description
*/

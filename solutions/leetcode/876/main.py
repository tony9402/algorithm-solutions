# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/middle-of-the-linked-list/submissions/2099179983/
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def middleNode(self, head: Optional[ListNode]) -> Optional[ListNode]:
        cur = head
        L = 0
        while cur:
            L += 1
            cur = cur.next

        cur = head
        for _ in range(L // 2):
            cur = cur.next

        return cur


""" Solution Description
첫 번째 순회에서 연결 리스트의 전체 길이 L을 구한다.
다시 head부터 L // 2번 이동하면 홀수 길이에서는 중앙 노드, 짝수 길이에서는 두 중앙 노드 중 두 번째 노드에 도착한다.
연결 리스트를 두 번 순회하므로 시간 복잡도는 O(N), 추가 공간 복잡도는 O(1)이다.
"""

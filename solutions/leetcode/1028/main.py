# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/submissions/1551445762
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def recoverFromPreorder(self, traversal: str) -> Optional[TreeNode]:
        V = list(map(int, [x for x in traversal.split('-') if x]))
        D = [0]
        push = True
        for ch in traversal:
            if ch == '-':
                if push:
                    D.append(0)
                    push = False
                D[-1] += 1
            else:
                push = True
        root = TreeNode(V[0])
        idx = 1
        st = [(root, 0)]
        while st and idx < len(V):
            while st and st[-1][1] >= D[idx]: st.pop(-1)
            if not st: break
            cur, d = st[-1]
            if cur.left is None:
                cur.left = TreeNode(V[idx])
                st.append((cur.left, D[idx]))
            elif cur.right is None:
                cur.right = TreeNode(V[idx])
                st.append((cur.right, D[idx]))
            idx += 1
        return root


""" Solution Description
"""

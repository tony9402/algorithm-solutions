# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/house-robber-iii/submissions/2111070576
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def rob(self, root: Optional[TreeNode]) -> int:
        def dfs(cur: Optional[TreeNode]) -> Tuple[int, int]:
            if not cur:
                return 0, 0
            left = dfs(cur.left)
            right = dfs(cur.right)
            return max(left) + max(right), cur.val + left[0] + right[0]

        return max(dfs(root))


""" Solution Description
"""

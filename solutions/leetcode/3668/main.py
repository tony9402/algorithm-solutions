# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/restore-finishing-order/submissions/2064969364
class Solution:
    def recoverOrder(self, order: List[int], friends: List[int]) -> List[int]:
        # friends = set(friends)
        return [x for x in order if x in friends]


""" Solution Description
"""

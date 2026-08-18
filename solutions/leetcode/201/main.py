# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/bitwise-and-of-numbers-range/submissions/1181948785
class Solution:
    def rangeBitwiseAnd(self, left: int, right: int) -> int:
        ret = 0
        while left < right:
            left >>= 1
            right >>= 1
            ret += 1
        return left << ret


""" Solution Description
"""

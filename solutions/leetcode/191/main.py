# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/number-of-1-bits/submissions/1108574065
class Solution:
    def hammingWeight(self, n: int) -> int:
        n = (n >>  1 & 0x55555555) + (n & 0x55555555)
        n = (n >>  2 & 0x33333333) + (n & 0x33333333)
        n = (n >>  4 & 0x0F0F0F0F) + (n & 0x0F0F0F0F)
        n = (n >>  8 & 0x00FF00FF) + (n & 0x00FF00FF)
        n = (n >> 16 & 0x0000FFFF) + (n & 0x0000FFFF)
        return n


""" Solution Description
"""

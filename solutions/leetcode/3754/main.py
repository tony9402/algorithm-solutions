# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-i/submissions/2058758002
from functools import reduce

class Solution:
    def sumAndMultiply(self, n: int) -> int:
        s = list(
            filter(
                lambda x: x != 0, list(map(int, list(str(n))))
            )
        )
        return sum(s) * int(''.join(map(str, s))) if s else 0


""" Solution Description
"""

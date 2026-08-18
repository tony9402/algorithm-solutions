# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/longest-subsequence-with-non-zero-bitwise-xor/submissions/2107743742
class Solution:
    def longestSubsequence(self, nums: List[int]) -> int:
        xors = 0
        found_not_zero = 0
        for x in nums:
            xors ^= x
            if x:
                found_not_zero = True

        if xors:
            return len(nums)

        return len(nums) - 1 if found_not_zero else 0


""" Solution Description
"""

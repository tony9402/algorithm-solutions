# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/number-of-strings-that-appear-as-substrings-in-word/submissions/2049411643
class Solution:
    def numOfStrings(self, patterns: List[str], word: str) -> int:
        return sum([int(x in word) for x in patterns])


""" Solution Description
"""

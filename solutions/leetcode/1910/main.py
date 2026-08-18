# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/remove-all-occurrences-of-a-substring/submissions/1539055569
class Solution:
    def removeOccurrences(self, s: str, part: str) -> str:
        while part in s:
            idx = s.find(part)
            s = f"{s[:idx]}{s[idx+len(part):]}"
        return s


""" Solution Description
"""

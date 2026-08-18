# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/submissions/2050979180
from collections import defaultdict

class Solution:
    def numberOfSubstrings(self, s: str) -> int:
        N = len(s)
        r = -1
        D = defaultdict(int)
        ans = 0
        for i in range(N):
            while r + 1 < N and len(D) < 3:
                D[s[r + 1]] += 1
                r += 1
            if len(D) == 3:
                ans += N - r
            D[s[i]] -= 1
            if D[s[i]] == 0:
                D.pop(s[i])
        return ans


""" Solution Description
"""

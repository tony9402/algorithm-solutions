# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/submissions/2106577436
class Solution:
    def maximumLengthSubstring(self, s: str) -> int:
        D = defaultdict(int)
        N = len(s)
        r = -1
        answer = 0
        for l in range(N):
            while r + 1 < N and D[s[r + 1]] < 2:
                r += 1
                D[s[r]] += 1

            answer = max(answer, r - l + 1)
            D[s[l]] -= 1

        return answer


""" Solution Description
"""

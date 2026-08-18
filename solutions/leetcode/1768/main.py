# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/merge-strings-alternately/submissions/2063807394
class Solution:
    def mergeAlternately(self, word1: str, word2: str) -> str:
        l, r = 0, 0
        N, M = len(word1), len(word2)

        ret = []
        while l < N and r < M:
            ret.append(word1[l])
            ret.append(word2[r])
            l += 1
            r += 1

        while l < N:
            ret.append(word1[l])
            l += 1

        while r < M:
            ret.append(word2[r])
            r += 1

        return "".join(ret)


""" Solution Description
"""

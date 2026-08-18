# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/group-anagrams/submissions/2064914433
from collections import defaultdict
class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        D = defaultdict(list)
        for x in strs:
            y = ''.join(sorted(x))
            D[y].append(x)

        answer = []
        for k, v in D.items():
            answer.append(v)

        return answer


""" Solution Description
"""

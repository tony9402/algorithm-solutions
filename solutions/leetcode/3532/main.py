# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/path-existence-queries-in-a-graph-i/submissions/2062380631
class Solution:
    def pathExistenceQueries(self, n: int, nums: List[int], maxDiff: int, queries: List[List[int]]) -> List[bool]:
        chk = [0 for _ in range(n)]
        for i in range(1, n):
            chk[i] = chk[i - 1] + int(nums[i] - nums[i - 1] > maxDiff)
        answer = [False for _ in range(len(queries))]
        for i, query in enumerate(queries):
            answer[i] = chk[query[0]] == chk[query[1]]
        return answer


""" Solution Description
"""

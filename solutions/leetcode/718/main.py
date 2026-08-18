# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/maximum-length-of-repeated-subarray/submissions/804238278
class Solution:
    def findLength(self, nums1: List[int], nums2: List[int]) -> int:
        N, M = len(nums1), len(nums2)
        DP = [[0 for j in range(M+1)] for i in range(N+1)]
        ans=0
        for i, x in enumerate(nums1):
            for j, y in enumerate(nums2):
                if x == y and DP[i+1][j+1]<DP[i][j]+1:
                    DP[i+1][j+1]=DP[i][j]+1
                if ans<DP[i+1][j+1]:
                    ans=DP[i+1][j+1]
        return ans


""" Solution Description
"""

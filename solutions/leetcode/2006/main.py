# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/count-number-of-pairs-with-absolute-difference-k/submissions/851679997
class Solution:
    def countKDifference(self, nums: List[int], k: int) -> int:
        MAXN = 100
        cnt = [0 for i in range(MAXN + 1)]
        for x in nums:
            cnt[x] += 1

        ans = 0
        for x in nums:
            if x - k >= 0:
                ans += cnt[x - k]
            if x + k <= MAXN:
                ans += cnt[x + k]
            cnt[x] -= 1
        return ans


""" Solution Description
"""

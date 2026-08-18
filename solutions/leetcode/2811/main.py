# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/check-if-it-is-possible-to-split-array/submissions/2105618024
class Solution:
    def canSplitArray(self, nums: List[int], m: int) -> bool:
        # 문제를 잘 읽어보면 길이가 N인 배열을 조건에 만족하도록 나누면서 길이가 1인 배열들로 나눌 수 있는지 물어본다.
        # 모두 다 나눠야하므로 길이가 2이하인 경우는 조건에 만족하도록 다 나눌 수 있고
        # 3 이상인 경우 인접한 두 원소의 합이 m보다 크거나 같으면 된다.
        #  -> 왜냐하면 인접한 두 수를 제외하고 계속 하나씩 분할하면 되기 때문이다.

        N = len(nums)

        if N <= 2:
            return True

        for i in range(1, N):
            if nums[i - 1] + nums[i] >= m:
                return True

        return False


""" Solution Description
"""

# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/maximum-subarray/submissions/2089874516
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        ans = -10000
        S = 0
        for x in nums:
            S = max(x, S + x)
            ans = max(ans, S)
        return ans


""" Solution Description
해당 알고리즘은 매우 유명한 알고리즘이다.
카데인 알고리즘 (kadane algorithm)

DP 방식으로 풀었으며 아래와 같이 점화식을 구할 수 있다.

DP[i]: 연속된 부분 수열 중 i번째 원소로 끝나는 수열의 합 중 최대인 값

if i == 0 : DP[i] = nums[0]
else      : DP[i] = max(nums[i], nums[i] + DP[i - 1])
"""
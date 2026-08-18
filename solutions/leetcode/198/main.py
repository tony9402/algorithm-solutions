# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/house-robber/submissions/2089828196/
class Solution:
    def rob(self, nums: List[int]) -> int:
        N = len(nums)
        DP = [0] * (N + 1)
        DP[1] = nums[0]
        for i in range(2, N + 1):
            DP[i] = max(DP[i - 1], DP[i - 2] + nums[i - 1])

        return DP[N]


""" Solution Description
DP[i]를 앞에서 i개의 집을 고려했을 때 훔칠 수 있는 최대 금액으로 정의한다.
i번째 집을 훔치지 않는 DP[i - 1]과, i번째 집을 훔치고 바로 전 집을 제외한 DP[i - 2] + nums[i - 1] 중 큰 값을 선택한다.
한 번의 순회로 계산하므로 시간 복잡도와 공간 복잡도는 각각 O(N)이다.
"""

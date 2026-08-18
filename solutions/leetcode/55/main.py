# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/jump-game/submissions/2081780346/
class Solution:
    def canJump(self, nums: List[int]) -> bool:
        N = len(nums)
        right = 0
        for i, x in enumerate(nums):
            if i <= right:
                right = max(right, i + x)
        return right >= N - 1


""" Solution Description
right에 지금까지 도달할 수 있는 가장 오른쪽 인덱스를 저장한다.
현재 인덱스 i가 right 이내일 때만 그 위치에서 점프할 수 있으므로 i + nums[i]로 도달 범위를 갱신한다.
마지막 인덱스까지 도달 범위가 이어지는지만 확인하면 되며 시간 복잡도는 O(N), 추가 공간 복잡도는 O(1)이다.
"""

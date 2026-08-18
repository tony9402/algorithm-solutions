# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/sort-array-by-parity/submissions/2098979188/
class Solution:
    def sortArrayByParity(self, nums: List[int]) -> List[int]:
        N = len(nums)
        left = 0
        for i in range(N):
            if nums[i] % 2 == 0:
                nums[left], nums[i] = nums[i], nums[left]
                left += 1
        return nums


""" Solution Description
left는 다음 짝수가 들어갈 위치를 가리킨다.
배열을 순회하다 짝수를 만나면 left 위치의 값과 교환하고 left를 한 칸 이동한다.
순회가 끝나면 left 앞에는 짝수만, 뒤에는 홀수만 남는다. 시간 복잡도는 O(N), 추가 공간 복잡도는 O(1)이다.
"""

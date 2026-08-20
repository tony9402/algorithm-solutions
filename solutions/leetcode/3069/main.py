# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/distribute-elements-into-two-arrays-i/submissions/2113323553
class Solution:
    def resultArray(self, nums: List[int]) -> List[int]:
        N = len(nums)

        left_array, right_array = [nums[0]], [nums[1]]

        for i in range(2, N):
            if left_array[-1] > right_array[-1]:
                left_array.append(nums[i])
            else:
                right_array.append(nums[i])
        
        return left_array + right_array

""" Solution Description
간단한 문제라 자세한 문제 풀이는 작성하지 않는다.

왼쪽 오른쪽 배열을 각각 만들고 조건에 맞게 왼쪽 또는 오른쪽에 원소를 넣고 마지막에 왼쪽 배열과 오른쪽 배열을 합치면 된다.
"""

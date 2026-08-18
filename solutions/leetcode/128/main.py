# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/longest-consecutive-sequence/submissions/2091352022/
class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        nums = set(nums)
        answer = 0
        for x in nums:
            if x - 1 not in nums:
                length = 1
                while x + length in nums:
                    length += 1
                answer = max(answer, length)

        return answer


""" Solution Description
중복을 제거한 숫자들을 집합에 저장한다.
x - 1이 집합에 없는 경우에만 x를 연속 수열의 시작점으로 보고 x + 1, x + 2를 차례로 확인해 길이를 센다.
각 숫자는 하나의 연속 수열에서만 확인되므로 평균 시간 복잡도는 O(N), 공간 복잡도는 O(N)이다.
"""

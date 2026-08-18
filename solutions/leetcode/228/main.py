# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/summary-ranges/submissions/2089853539
class Solution:
    def summaryRanges(self, nums: List[int]) -> List[str]:
        answer = []
        idx = 0
        N = len(nums)
        while idx < N:
            nxt = idx
            while nxt + 1 < N and nums[nxt] + 1 == nums[nxt + 1]:
                nxt += 1

            if nxt == idx:
                answer.append(str(nums[idx]))
            else:
                answer.append(f"{nums[idx]}->{nums[nxt]}")

            idx = nxt + 1

        return answer


""" Solution Description
문제 조건이 정렬되어 있고 중복 원소가 없다.
특별히 다른 부분은 없고 문제에 나와있는대로 구현하면 되는 문제이다.
"""

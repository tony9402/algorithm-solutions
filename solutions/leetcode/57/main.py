# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/insert-interval/submissions/2099288506/
class Solution:
    def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:
        N = len(intervals)
        answer = []
        idx = 0

        while idx < N and intervals[idx][1] < newInterval[0]:
            answer.append(intervals[idx])
            idx += 1

        while idx < N and intervals[idx][0] <= newInterval[1]:
            newInterval[0] = min(newInterval[0], intervals[idx][0])
            newInterval[1] = max(newInterval[1], intervals[idx][1])
            idx += 1

        answer.append(newInterval)

        while idx < N:
            answer.append(intervals[idx])
            idx += 1

        return answer


""" Solution Description
정렬된 구간을 새 구간의 왼쪽에 있는 구간, 겹치는 구간, 오른쪽에 있는 구간의 세 부분으로 나눈다.
왼쪽 구간은 그대로 추가하고, 겹치는 동안 새 구간의 양 끝을 확장한 뒤 합쳐진 새 구간을 한 번 추가한다.
이후 남은 오른쪽 구간도 그대로 추가한다. 모든 구간을 한 번 확인하므로 시간 복잡도는 O(N), 정답을 제외한 추가 공간 복잡도는 O(1)이다.
"""

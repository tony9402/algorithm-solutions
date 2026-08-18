# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/car-fleet/submissions/2099232871/
class Solution:
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
        arr = sorted(zip(position, speed), reverse=True)
        arrive_times = [(target - p) / s for p, s in arr]

        answer = 0
        current_t = 0
        for t in arrive_times:
            if t > current_t:
                answer += 1
                current_t = t

        return answer


""" Solution Description
차량을 목표 지점에 가까운 순서로 정렬하고 각 차량이 혼자 달릴 때의 도착 시간을 계산한다.
뒤 차량의 도착 시간이 앞 fleet의 도착 시간보다 작거나 같으면 도착 전에 따라잡으므로 같은 fleet에 속한다.
더 늦게 도착하는 차량만 새로운 fleet의 선두가 된다. 정렬 때문에 시간 복잡도는 O(N log N), 공간 복잡도는 O(N)이다.
"""

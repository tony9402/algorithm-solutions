# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/daily-temperatures/submissions/2091240880/
class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        stack = []
        N = len(temperatures)
        answer = [0 for _ in range(N)]
        for i, x in enumerate(temperatures):
            while stack and stack[-1][0] < x:
                answer[stack[-1][1]] = i - stack[-1][1]
                stack.pop()
            stack.append((x, i))

        return answer


""" Solution Description
아직 더 따뜻한 날을 찾지 못한 날짜를 온도가 내림차순이 되도록 스택에 보관한다.
현재 온도가 스택의 마지막 온도보다 높으면 그 날짜의 기다린 일수는 두 인덱스의 차이이므로 정답을 채우고 스택에서 제거한다.
각 날짜가 스택에 한 번 들어가고 한 번 나오므로 시간 복잡도와 공간 복잡도는 O(N)이다.
"""

# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/spiral-matrix/submissions/2089813713/
class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        answer = []
        y, x, d = 0, 0, 0
        dy = (0, 1, 0, -1)
        dx = (1, 0, -1, 0)
        CHECK_VALUE = -101

        N, M = len(matrix), len(matrix[0])

        def is_inside(cur_y: int, cur_x: int) -> bool:
            return 0 <= cur_y < N and 0 <= cur_x < M

        def can_go(cur_y: int, cur_x: int) -> bool:
            return is_inside(cur_y, cur_x) and matrix[cur_y][cur_x] != CHECK_VALUE

        for _ in range(N * M):
            answer.append(matrix[y][x])
            matrix[y][x] = CHECK_VALUE
            ny, nx = y + dy[d], x + dx[d]
            if not can_go(ny, nx):
                d = (d + 1) % 4
            y, x = y + dy[d], x + dx[d]
        return answer


""" Solution Description
오른쪽, 아래, 왼쪽, 위 순서로 이동하면서 현재 값을 정답에 추가한다.
방문한 칸은 입력 범위 밖의 값인 -101로 표시하고, 다음 칸이 범위를 벗어나거나 이미 방문한 칸이면 방향을 시계 방향으로 바꾼다.
모든 칸을 한 번씩 방문하므로 시간 복잡도는 O(NM)이고, 정답 배열을 제외한 추가 공간 복잡도는 O(1)이다.
"""

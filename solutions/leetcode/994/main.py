# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/rotting-oranges/submissions/2081802773/
from collections import deque


class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        N = len(grid)
        M = len(grid[0])

        dy = (-1, 1, 0, 0)
        dx = (0, 0, -1, 1)

        dq = deque()
        cnt = 0
        for i in range(N):
            for j in range(M):
                if grid[i][j] > 0:
                    cnt += 1
                if grid[i][j] == 2:
                    dq.append((i, j))

        if cnt == 0:
            return 0

        answer = -1
        while dq:
            dq_len = len(dq)
            answer += 1
            for _ in range(dq_len):
                y, x = dq.popleft()
                cnt -= 1
                for k in range(4):
                    qy, qx = y + dy[k], x + dx[k]
                    if 0 > qy or qy >= N or 0 > qx or qx >= M:
                        continue
                    if grid[qy][qx] == 1:
                        grid[qy][qx] = 2
                        dq.append((qy, qx))

        if cnt != 0:
            answer = -1

        return answer


""" Solution Description
처음부터 썩어 있는 모든 오렌지를 큐에 넣고 동시에 퍼져 나가는 다중 시작점 BFS를 수행한다.
한 BFS 레벨이 1분을 뜻하며, 새로 썩은 오렌지는 즉시 2로 표시해 중복 방문을 막는다.
BFS가 끝난 뒤 처리되지 않은 오렌지가 남으면 -1을 반환한다. 시간과 공간 복잡도는 모두 O(NM)이다.
"""

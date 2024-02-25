# Authored by : 220v
# Co-authored by : tony9402
# Link : http://boj.kr/d80c341225ce4988805cca9a6a201a84
import sys
from collections import deque
from itertools import combinations

def input():
    return sys.stdin.readline().rstrip()

# input
N, M = map(int, input().split())
lab = [list(map(int, input().split())) for _ in range(N)]

# delta row, delta col.
dr = (1, 0, -1, 0)
dc = (0, 1, 0, -1)

# save Minimum Second to infect all blocks.
INF = 1000000
minSec = INF

# find 2 in laboratory / change numbers(wall, virus)
twos = []
for r, row in enumerate(lab):
    for c, i in enumerate(row):
        if i == 2:
            twos.append([r, c])
            lab[r][c] = "*"
        elif i == 1:
            lab[r][c] = "-"


def check(inLab):
    maxCount = 0  # 최단 거리 계산
    for two in twos:
        inLab[two[0]][two[1]] = "*"

    for i in range(N):
        for j in range(N):
            if inLab[i][j] == 0:
                return INF

            if inLab[i][j] != '*' and inLab[i][j] != '-':
                maxCount = max(maxCount, inLab[i][j])

    return maxCount


# cycle of combinations
# Combination - (len of twos) C (M) - find all combination of index.
for s in combinations(twos, M):
    sec = 0
    q = deque(s)
    templab = [row[:] for row in lab]

    # BFS - one cycle (1 case)
    while q:
        sec += 1
        cntq = len(q)

        # BFS - one cycle (1 sec)
        while cntq > 0:
            r, c = q.popleft()
            cntq -= 1

            for i in range(4):
                nr, nc = r + dr[i], c + dc[i]
                # check if wall / if virus already infected.
                if 0 <= nr < N and 0 <= nc < N and (templab[nr][nc] == 0 or templab[nr][nc] == "*"):
                    q.append([nr, nc])
                    # save sec for infect this block.
                    templab[nr][nc] = sec

    minSec = min(minSec, check(templab))

if minSec == INF:
    print(-1)
else:
    print(minSec)

""" Solution Description
'비활성화된 바이러스 또한 전염이 진행될 수 있도록 처리할 것.'  
'비활성화된 바이러스가 활성화되는 것은 최소 시간을 측정하는 데에 고려하지 않아야 할 것.'  
위 두 가지 조건과, 시간 초과가 나지 않도록 신경쓰며 BFS를 이용해 문제를 풀이한다.  
https://wondev.tistory.com/157  
"""

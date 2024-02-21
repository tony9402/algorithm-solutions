# Authored by : 220v
# Co-authored by : -
# Link : https://www.acmicpc.net/source/61069486
import sys
import copy
from collections import deque
from itertools import combinations

def input():
    return sys.stdin.readline().rstrip()

# input
N, M = map(int, input().split())
lab = []
for _ in range(N):
    lab.append(list(map(int, input().split())))

# delta row, delta col.
dr = [1, 0, -1, 0]
dc = [0, 1, 0, -1]

# find 2 in laboratory / count 0 in lab / change numbers(wall, virus)
twos = []
cnt_0 = 0
for r, row in enumerate(lab):
    for c, i in enumerate(row):
        if i == 2:
            twos.append([r, c])
            lab[r][c] = "*"
        elif i == 1:
            lab[r][c] = "-"
        elif i == 0:
            cnt_0 += 1

# Combination - (len of twos) C (M) - find all combination of index.
start = list(combinations(twos, M))

# save Minimum Second to infect all blocks.
minSec = 1000000

def isAllInfected(inLab):
    # function to know all blocks infected.
    for row in inLab:
        for c in row:
            if c == 0:
                return False

    return True

# check if minSec = 0
if isAllInfected(lab):
    print(0)
    exit()

def check(inLab):
    count0 = 0  # 0의 갯수 확인
    maxCount = 0  # 최단 거리 계산
    for two in twos:
        inLab[two[0]][two[1]] = "*"

    for i in range(N):
        for j in range(N):
            if inLab[i][j] == 0:
                return -1

            if inLab[i][j] != '*' and inLab[i][j] != '-':
                maxCount = max(maxCount, inLab[i][j])

    if count0 == 0:
        return maxCount

# cycle of combinations
for s in start:
    sec = 0
    q = deque(s)
    templab = copy.deepcopy(lab)

    # BFS - one cycle (1 case)
    while q:
        sec += 1
        tempq = deque()

        # BFS - one cycle (1 sec)
        while q:
            r, c = q.popleft()

            for i in range(4):
                nr = r + dr[i]
                nc = c + dc[i]
                # check if wall / if virus already infected.
                if N > nr >= 0 and N > nc >= 0 and (templab[nr][nc] == 0 or templab[nr][nc] == "*"):
                    tempq.append([nr, nc])
                    # save sec for infect this block.
                    templab[nr][nc] = sec

        q = tempq

    a = check(templab)
    if a != -1 and minSec > a:
        minSec = a

if minSec != 1000000:
    print(minSec)
else:
    print(-1)

""" Solution Description
'비활성화된 바이러스 또한 전염이 진행될 수 있도록 처리할 것.'
'비활성화된 바이러스가 활성화되는 것은 최소 시간을 측정하는 데에 고려하지 않아야 할 것.'
위 두 가지 조건과, 시간 초과가 나지 않도록 신경쓰며 BFS를 이용해 문제를 풀이한다.
https://wondev.tistory.com/157
"""
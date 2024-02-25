# Authored by : 220v
# Co-authored by : -
# Link : https://www.acmicpc.net/source/68292211
import sys
from collections import deque

def input():
    return sys.stdin.readline().rstrip()

N, M = map(int, input().split())

p = [list(map(int, input().split())) for _ in range(N)]
    
dr = (1, 0, -1, 0)
dc = (0, 1, 0, -1)

air = [[1]*M for _ in range(N)]

def BFS(r, c):
    deq = deque([(r, c)])
    while deq:
        nr, nc = deq.popleft()
        for i in range(4):
            lr, lc = nr+dr[i], nc+dc[i]
        
            # 격자 벗어남 체크 / 공기 칸인지 체크 / bfs에서 이미 지나간 칸인 지 확인 (air[lr][lc])
            if 0 <= lr < N and 0 <= lc < M and p[lr][lc] == 0 and air[lr][lc] == 1:
                air[lr][lc] = 0
                deq.append((lr, lc))

T = 0   # 걸린 시간
while True:
    T += 1
    air = [[1]*M for _ in range(N)]
    
    # 공기가 확산되는 칸을 check.
    for r in range(N):
        for c in range(M):
            # 치즈가 있는 칸이거나, 이미 외부 공기와 통한다고 체크한 칸은 pass.
            if p[r][c] == 1 or air[r][c] == 0:
                continue
            
            # 현재 칸이 외부와 닿아 있으면 isAirExposed = True.
            isAirExposed = False
            for i in range(4):
                lr, lc = r+dr[i], c+dc[i]
                if lr < 0 or lr >= N or lc < 0 or lc >= M:
                    isAirExposed = True
                    break
            
            # 외부와 맞닿은 칸부터 BFS로 공기인 칸을 탐색하며 외부 공기와 통하는 것으로 check (0으로 변경)
            if isAirExposed:
                BFS(r, c)

    # 치즈 녹이기
    for r in range(N):
        for c in range(M):
            if p[r][c] == 0:
                continue
            
            cnt = 0
            for i in range(4):
                lr, lc = r+dr[i], c+dc[i]
                if air[lr][lc] == 0:
                    cnt += 1
            # 외부 공기와 2변 이상 닿으면, 치즈를 녹인다.
            if cnt >= 2:
                p[r][c] = 0

    # 다 녹음 체크
    isAllMelt = True
    for r in range(N):
        if not isAllMelt:
            break
        for c in range(M):
            if p[r][c] == 1:
                isAllMelt = False
                break
    
    if isAllMelt:
        print(T)
        break
    
""" Solution Description
두 변 이상 실내온도의 공기와 접촉할 때 치즈가 녹는다는 조건만 잘 처리한다면, 여타 BFS 문제와 비슷하게 풀이할 수 있다.  
https://wondev.tistory.com/202
"""

# Authored by : 220v
# Co-authored by : -
# Link : https://www.acmicpc.net/source/58245171
import sys
from collections import deque

def input():
    return sys.stdin.readline().rstrip()

def solve():
    N, K = map(int, input().split())

    deq = deque([N])
    visit = dict()
    visit[N] = 0
    
    while deq:
        cur = deq.popleft()
        if cur == K:
            print(visit[cur])
            return

        for nxt in (cur*2, cur+1, cur-1):
            if 0 <= nxt <= 100000 and visit.get(nxt, -1) == -1:
                deq.append(nxt)
                visit[nxt] = visit[cur]+1

solve()

""" Solution Description
시간 초과나 메모리 초과가 나지 않도록 100,000 이하에서 BFS가 진행되도록 조건을 걸어줘야 하는 것을 주의하며 풀이.  
자세한 풀이: https://wondev.tistory.com/126
"""

# Authored by : 220v
# Co-authored by : -
# Link : https://www.acmicpc.net/source/58245171
import sys
from collections import deque

def input():
    return sys.stdin.readline().rstrip()

def sol():
    N, K = map(int, input().split())

    deq = deque([N])
    visit = dict()
    visit[N] = 0
    
    while deq:
        a = deq.popleft()
        if a == K:
            print(visit[a])
            return

        for i in [a*2, a+1, a-1]:
            if 0 <= i <= 100000 and visit.get(i, -1) == -1:
                deq.append(i)
                visit[i] = visit[a]+1

sol()

""" Solution Description
시간 초과나 메모리 초과가 나지 않도록 100,000 이하에서 BFS가 진행되도록 조건을 걸어줘야 하는 것을 주의하며 풀이.
https://wondev.tistory.com/126
"""
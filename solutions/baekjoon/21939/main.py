# Authored by: tony9402
# Co-authored by: -
# Link: http://boj.kr/87e29ae241204a7d923fff68d173bcc9
import sys
import heapq

def input():
    return sys.stdin.readline().rstrip()

mx_heap, mn_heap = [], []
level = [0] * 100001

def recommend(x):
    while len(mx_heap):
        l, p = mx_heap[0]
        if level[-p] == -l: break
        heapq.heappop(mx_heap)
    while len(mn_heap):
        l, p = mn_heap[0]
        if level[p] == l: break
        heapq.heappop(mn_heap)
    print(-mx_heap[0][1] if x == 1 else mn_heap[0][1])

def add(p, l):
    heapq.heappush(mx_heap, (-l, -p))
    heapq.heappush(mn_heap, (l, p))
    level[p] = l

def solved(p):
    level[p] = 0

N = int(input())
for i in range(N):
    P, L = map(int, input().split())
    add(P, L)

Q = int(input())
for i in range(Q):
    cmd, *args = input().split()
    args = list(map(int, args))
    if cmd == 'solved':
        solved(args[0])
    elif cmd == 'recommend':
        recommend(args[0])
    else:
        add(args[0], args[1])

""" Solution Description
난이도 L과 문제번호 P를 (L, P) 쌍으로 두 개의 heap(힙, 우선순위 큐)로 관리하면 편리하게 최대, 최소를 빠르게 구할 수 있다.
"""
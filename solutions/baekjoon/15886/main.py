# Authored by : hyeonjaee
# Co-authored by : -
# Link : http://boj.kr/f9cd00a87d59430abd180cfe4050d394
import sys

def input():
    return sys.stdin.readline().rstrip()

n = int(input())
board = input()
ans = sum(1 for i in range(n-1) if board[i] == 'E' and board[i+1] == 'W')
print(ans)

""" Solution Description
이동방향이 전환되는 곳, 즉 E 뒤에  W가 이어서 나오는 곳에 선물을 놓아야 한다.
따라서 입력 받은 리스트에서 E 다음에 W가 나오면 ans를 1씩 증가한다.
"""

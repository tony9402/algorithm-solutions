# Authored by : leejh9226
# Co-authored by : -
# Link : http://boj.kr/171a010d7b2247588d9dba8b3fa192c2


import heapq
import sys

input = sys.stdin.readline


max_g_heap = [[] for _ in range(101)]
min_g_heap = [[] for _ in range(101)]
max_l_heap = [[] for _ in range(101)]
min_l_heap = [[] for _ in range(101)]

l_lookup = [0] * 100001
g_lookup = [0] * 100001

removed = set()


def add(p, l, g):
    """
    recommend에서 사용할 수 있도록 알고리즘 유형, 난이도별로 생성해둔 최소, 최대힙에 문제를 추가

    Q. 삭제된 적이 있지만 아직 heap에 해당 문제가 남아있을 수 있지 않나요?
    A. heap에는 삭제된 문제가 남아있을 수 있어, 동일한 문제를 추가하면 해당 heap에는 똑같은 문제 2개가 존재하게 됨. 하지만 이후 해당
    문제를 다시한번 삭제한 다음 조회하는 경우 두 문제 모두 efficient_top_g 함수에서 제거되기 때문에 문제가 발생하지 않음. 문제를 다시
    삭제하기 이전이라면, 둘 중 어떤 문제(인스턴스)가 조회되더라도 동일한 답이 나오기 때문에 문제가 발생하지 않음.
    """

    # 각각 100001, 101보다 큰 2진수 값(2**17, 2**7)을 곱하여 integer값 하나에 3가지 정보를 담음. 이 값을 lpg라고 명명
    lpg = l << 24 | p << 7 | g

    # 동일한 난이도, 문제번호, 알고리즘 유형의 문제가 이미 삭제된 적이 있다면, 삭제된 기록을 제거
    if is_removed(lpg):
        removed.remove(lpg)

    # 난이도 > 문제번호 > 알고리즘 유형 우선순위로 정렬(최소, 최대힙)
    heapq.heappush(max_g_heap[G], -lpg)
    heapq.heappush(min_g_heap[G], lpg)
    heapq.heappush(max_l_heap[L], -lpg)
    heapq.heappush(min_l_heap[L], lpg)
    # solved에서 사용할 수 있도록 문제번호-난이도, 문제번호-알고리즘 유형 매핑 정보를 저장
    l_lookup[P] = l
    g_lookup[P] = g


def remove(p, l, g):
    """
    난이도, 문제번호, 알고리즘 유형으로 식별되는 유일한 문제를 "삭제되었음"으로 표시
    - 실제 힙에서 삭제하는 동작은, recommend에서 heappop을 호출할 때 "삭제되었음"으로 표시된 문제를 제거하는 것
    """
    removed.add(l << 24 | p << 7 | g)


def is_removed(lpg):
    """
    난이도, 문제번호, 알고리즘 유형으로 식별되는 유일한 문제가 제거되었는지 확인
    max_heap에서는 음수 값으로 저장되어 있으므로, 절대값을 취한 뒤 비교
    """
    if abs(lpg) in removed:
        return True
    return False


def efficient_top(target_heap):
    """
    최상위 문제가 이미 제거된 문제라면, 최상위 문제를 제거하고 다음 최상위 문제를 찾음
    삭제되지 않고, 조건을 만족하는 문제가 존재한다면, 문제번호를 반환
    """
    while target_heap and is_removed(target_heap[0]):
        heapq.heappop(target_heap)

    if target_heap:
        return (abs(target_heap[0]) >> 7) & 0x1FFFF
    return None


n = int(input())
for _ in range(n):
    P, L, G = map(int, input().split())
    add(P, L, G)

q = int(input())
for _ in range(q):
    cmd = input().split()

    # case 분기
    match cmd[0]:
        case "recommend":
            """
            recommend G x
            x가 1인경우 -> 알고리즘 분류가 G인 문제중 가장 어려운것 출력
                조건을 만족하는 문제가 많다면 문제번호가 큰것
            x가 -1인경우 -> 알고리즘 분류가 G인 문제중 가장 쉬운것 출력
                조건을 만족하는 문제가 많다면 문제번호가 작은것
                
            알고리즘 분류 G마다 각각의 최대, 최소힙을 사용하여 문제를 저장한다.
            - 힙 정렬 기준은 난이도 > 문제번호 > 알고리즘 분류 순서대로
            - 알고리즘 분류를 포함한 이유는, 힙에서 꺼낸 문제를 유일하게 식별하여 이미 풀린 문제인지 확인하기 위함
            """
            G, x = int(cmd[1]), int(cmd[2])
            if x == 1:
                print(efficient_top(max_g_heap[G]))
            else:
                print(efficient_top(min_g_heap[G]))
        case "recommend2":
            """
            recommend2 x
            x가 1인경우 -> 가장 어려운 문제 출력
                조건을 만족하는 문제가 많다면 문제번호가 큰것
            x가 -1인경우 -> 가장 쉬운 문제 출력
                조건을 만족하는 문제가 많다면 문제번호가 작은것
                
            난이도 L마다 각각의 최대, 최소힙을 사용하여 문제를 저장한다.
            - 힙 정렬 기준은 난이도 > 문제번호 > 알고리즘 분류 순서대로
            - 난이도를 포함한 이유는, 힙에서 꺼낸 문제를 유일하게 식별하여 이미 풀린 문제인지 확인하기 위함
            - x == 1인 경우 -> 난이도 100부터 1까지 순회하며, 해당 난이도에서 문제번호가 가장 큰 문제를 출력
            - x == -1인 경우 -> 난이도 1부터 100까지 순회하며, 해당 난이도에서 문제번호가 가장 작은 문제를 출력
            """
            x = int(cmd[1])
            if x == 1:
                for i in range(100, 0, -1):
                    if (a := efficient_top(max_l_heap[i])) is not None:
                        print(a)
                        break
            else:
                for i in range(1, 101, 1):
                    if (a := efficient_top(min_l_heap[i])) is not None:
                        print(a)
                        break
        case "recommend3":
            """
            recommend3 x L
            x가 1인경우 -> 난이도가 L이상인 문제 중 가장 쉬운것 출력
                조건을 만족하는 문제가 많다면 문제번호가 작은것
                없다면 -1 출력
            x가 -1인경우 -> 난이도가 L미만인 문제 중 가장 어려운것 출력
                조건을 만족하는 문제가 많다면 문제번호가 큰것
                없다면 -1 출력
                
            난이도 L마다 각각의 최대, 최소힙을 사용하여 문제를 저장한다.
            - 힙 정렬 기준은 난이도 > 문제번호 > 알고리즘 분류 순서대로
            - 난이도를 포함한 이유는, 힙에서 꺼낸 문제를 유일하게 식별하여 이미 풀린 문제인지 확인하기 위함
            - x == 1인 경우 -> 난이도 L부터 100까지 순회하며, 해당 난이도에서 문제번호가 가장 작은 문제를 출력
            - x == -1인 경우 -> 난이도 L-1부터 1까지 순회하며, 해당 난이도에서 문제번호가 가장 큰 문제를 출력
            """
            x, L = int(cmd[1]), int(cmd[2])
            if x == 1:
                for i in range(L, 101):
                    if (a := efficient_top(min_l_heap[i])) is not None:
                        print(a)
                        break
                else:
                    print(-1)
            else:
                for i in range(L - 1, 0, -1):
                    if (a := efficient_top(max_l_heap[i])) is not None:
                        print(a)
                        break
                else:
                    print(-1)
        case "add":
            P, L, G = int(cmd[1]), int(cmd[2]), int(cmd[3])
            add(P, L, G)
        case _:  # "solved"
            P = int(cmd[1])
            remove(P, l_lookup[P], g_lookup[P])

"""
알고리즘 유형, 난이도별로 최대, 최소힙을 사용하여 문제를 저장하고, 힙에서 문제를 꺼낼 때 이미 삭제된 문제인지 확인한 다음, 조건에
맞게 문제 번호를 출력했습니다.
"""

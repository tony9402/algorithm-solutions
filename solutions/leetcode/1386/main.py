# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/cinema-seat-allocation/submissions/2112060595
class Solution:
    def maxNumberOfFamilies(self, n: int, reservedSeats: List[List[int]]) -> int:
        G = defaultdict(lambda: 0b1111111111)
        chk = [
            (0b0111111110, 2),
            (0b0111100000, 1),
            (0b0000011110, 1),
            (0b0001111000, 1),
        ]
        for x in reservedSeats:
            a, b = x[0], x[1] - 1
            G[a] = G[a] & ~(1 << b)
        
        answer = (n - len(G)) * 2
        for v in G.values():
            for a, b in chk:
                if v & a == a:
                    answer += b
                    break
        
        return answer

""" Solution Description
n은 10^9 이지만 가로 줄에 아무 예약도 없는 경우는 항상 2가 된다.
따라서, 이미 예약되어 있는 가로 줄들만 보면 되고 이거에 대한 최대 개수는 min(10 * n, 10000) 이다. 이는 n이 아무리 커져도 10000을 넘지 못하므로 이미 예약된 자리들만 쭉 보면서 가능한 경우만 세주면 된다.
예약 가능한 자리를 1, 이미 예약된 자리를 0으로 뒀을 때 Case Work를 통해 답을 구해주면 된다.

1. 이미 예약된 자리 제외하고는 항상 2 ~ 5, 6 ~ 9 에 배치하면 최대이므로 (n - 이미 예약된 가로 줄 수) * 2가 된다.
2. 이미 예약된 자리를 0으로 만들면서 어떤 라인을 보면 되는지 기록한다.
3. 미리 전처리를 통해 2 ~ 5, 6 ~ 9를 앉을 수 있으면 2를 더하고 2 ~ 5, 6 ~ 9, 4 ~ 7 중 하나 예약가능한 자리면 1을 더한다.

위 시간복잡도는 대략 O(4 * 10000) 정도로 시간 내에 충분히 돌아간다.
"""

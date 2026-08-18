# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/find-pivot-index/submissions/2089873539
class Solution:
    def pivotIndex(self, nums: List[int]) -> int:
        N = len(nums)
        left_sum = 0
        right_sum = sum(nums)
        for i in range(N):
            cur = nums[i]
            right_sum -= cur
            if left_sum == right_sum:
                return i
            left_sum += cur

        return -1


""" Solution Description
특정 pivot 기준으로 왼쪽과 오른쪽 각각 합이 같아야 한다.
길이가 최대 10^4라 O(N^2)으로 풀어도 되겠지만 아래와 같이 풀면 O(N)으로 풀 수 있다.

1. 전체 합 S 구하기 (전처리). 이때, 왼쪽 합은 0이고 오른쪽 합은 S이다.
2. 맨 왼쪽부터 보면서 모든 원소를 볼 때까지 아래 3가지를 반복한다. 단, 중간에 멈춰야하는 경우 반복을 종료하면 된다.
    - 현재 보는 값은 pivot으로 둔다. 합 S에서 선택된거다보니 S에서 그 값을 제외한다.
    - 왼쪽 합과 오른쪽 합(S)이 같다면 현재 pivot에 대한 인덱스를 리턴한다.
    - 현재 pivot을 왼쪽 합으로 넘긴다.
"""

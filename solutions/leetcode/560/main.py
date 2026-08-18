# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/subarray-sum-equals-k/submissions/2091165484/
class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        N = len(nums)
        answer = 0
        D = defaultdict(int)
        D[0] = 1
        prefix_sum = 0
        for i in range(N):
            prefix_sum += nums[i]
            answer += D[prefix_sum - k]
            D[prefix_sum] += 1

        return answer


""" Solution Description
현재까지의 누적 합이 S일 때 앞에서 누적 합이 S - k였던 위치 다음부터 현재까지의 부분 배열 합은 k가 된다.
딕셔너리에 이전 누적 합의 등장 횟수를 저장하고, 각 위치에서 S - k의 개수만큼 정답에 더한다.
빈 구간의 누적 합 0도 한 번 기록해야 처음부터 시작하는 부분 배열을 셀 수 있다. 시간과 공간 복잡도는 O(N)이다.
"""

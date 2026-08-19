# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/find-the-largest-almost-missing-integer/submissions/2112051064
class Solution:
    def largestInteger(self, nums: List[int], k: int) -> int:
        N = len(nums)
        if N == k:
            return max(nums)
        cnt = [0 for _ in range(51)]
        for x in nums:
            cnt[x] += 1
        
        if k == 1:
            for i in range(50, -1, -1):
                if cnt[i] == 1:
                    return i
            return -1

        answer = -1
        if cnt[nums[0]] == 1:
            answer = nums[0]
        if cnt[nums[-1]] == 1:
            answer = max(answer, nums[-1])
        
        return answer


""" Solution Description
Case Work가 떠올랐다. 여기서 약간 헷갈렸던 부분이 있다.
연속된 부분 수열 안에서 중복된 원소가 있다 하다러도 다른 연속된 부분 수열에 등장하지 않으므로 답이 될 수 있다.
이런 경우는 k값이 nums의 길이가 같은 경우이다.

N: nums의 길이 (원소 개수)
k = N 인 경우
- 나올 수 있는 연속된 부분 수열이 한 가지 밖에 없으므로 nums 배열 중 최대값인 원소를 구하면 된다.
- -1인 경우는 없다.
k = 1 인 경우
- 모든 원소를 보면서 단 한번만 등장하는 원소 중 최댓값이 답이다.
- 위에서 답이 존재하지 않는다면 -1이 답이다.
1 < k < N 인 경우
- 맨 왼쪽 원소와 맨 오른쪽 원소를 제외하고는 다른 연속된 부분 수열에 등장하므로 맨 왼쪽과 맨 오른쪽만 단 한번만 등장하는 수인지 확인하면 된다.
- 위에서 답이 존재하지 않는다면 -1이 답이다.
"""

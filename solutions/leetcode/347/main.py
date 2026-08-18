# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/top-k-frequent-elements/submissions/2073464129/
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        N = len(nums)
        freq = defaultdict(int)
        bucket = defaultdict(set)

        for x in nums:
            freq[x] += 1

        for key, value in freq.items():
            bucket[value].add(key)

        answer = []
        for i in range(N + 1, 0, -1):
            for x in bucket[i]:
                if len(answer) == k:
                    break
                answer.append(x)
            if len(answer) == k:
                break

        return answer


""" Solution Description
각 숫자의 등장 횟수를 센 뒤, 등장 횟수를 인덱스처럼 사용하는 버킷에 숫자를 모은다.
가능한 가장 큰 빈도 N부터 역순으로 버킷을 확인하며 숫자 k개를 정답에 추가한다.
정렬하지 않고 빈도를 순회하므로 시간 복잡도와 공간 복잡도는 모두 O(N)이다.
"""

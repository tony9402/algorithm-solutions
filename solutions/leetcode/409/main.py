# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/longest-palindrome/submissions/2098999581/
class Solution:
    def longestPalindrome(self, s: str) -> int:
        cnt = defaultdict(int)
        for ch in s:
            cnt[ch] += 1

        answer = 0
        odd_cnt = 0
        for ch in cnt:
            c = cnt[ch]
            answer += c // 2 * 2
            cnt[ch] %= 2
            if cnt[ch]:
                odd_cnt += 1

        return answer + (1 if odd_cnt else 0)


""" Solution Description
팰린드롬의 양쪽에는 같은 문자를 짝수 개씩 배치할 수 있으므로 각 문자 개수에서 가장 큰 짝수를 모두 더한다.
홀수 개 남는 문자가 하나라도 있다면 그중 한 문자를 팰린드롬의 중앙에 놓을 수 있어 길이에 1을 추가한다.
문자열 길이를 N, 서로 다른 문자 수를 K라고 할 때 시간 복잡도는 O(N + K), 공간 복잡도는 O(K)이다.
"""

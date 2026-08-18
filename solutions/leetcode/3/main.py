# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/longest-substring-without-repeating-characters/submissions/2073223295/
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        N = len(s)
        r = -1
        D = set()
        ans = 0
        for i in range(N):
            while r + 1 < N and s[r + 1] not in D:
                D.add(s[r + 1])
                r += 1
            ans = max(ans, r - i + 1)
            D.discard(s[i])
        return ans


""" Solution Description
집합 D에 현재 구간의 문자들을 보관하는 슬라이딩 윈도우를 사용한다.
왼쪽 끝 i마다 다음 문자가 중복되지 않는 동안 오른쪽 끝 r을 확장하고 구간의 최대 길이를 갱신한 뒤 s[i]를 제거한다.
각 문자는 집합에 최대 한 번 들어가고 한 번 나오므로 시간 복잡도는 O(N), 공간 복잡도는 O(K)이다.
"""

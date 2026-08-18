# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/word-break/submissions/2073450535/
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        N, M = len(s), len(wordDict)

        DP = [0 for _ in range(N + 1)]
        DP[0] = 1
        for i in range(1, N + 1):
            for x in wordDict:
                if s[i - 1:i - 1 + len(x)] == x:
                    DP[i + len(x) - 1] |= DP[i - 1]

        return bool(DP[N])


""" Solution Description
DP[i]는 문자열의 앞 i개 문자를 사전의 단어들로 만들 수 있는지를 나타내며, 빈 문자열인 DP[0]은 참이다.
만들 수 있는 위치 다음에서 각 사전 단어와 같은 부분 문자열을 찾으면 그 단어의 마지막 위치까지 만들 수 있다고 표시한다.
문자열 길이를 N, 단어 수를 M, 단어의 최대 길이를 L이라고 할 때 시간 복잡도는 O(NML), 공간 복잡도는 O(N)이다.
"""

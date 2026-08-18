# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/longest-common-prefix/submissions/2076863712
class Solution:
    def longestCommonPrefix(self, strs: List[str]) -> str:

        length = min([len(x) for x in strs])
        N = len(strs)

        for l in range(length):
            flag = True
            for i in range(1, N):
                if strs[i][l] != strs[0][l]:
                    flag = False
                    break

            if not flag:
                return strs[0][:l]

        return strs[0][:length]


""" Solution Description
Longest Common Prefix의 길이의 최댓값(length)은 문자열들 길이 중 최솟값이다.
문자열 길이 제한(L)이 200이고 문자열 개수(N)도 최대 200이기 때문에 O(NL)로 1초이내로 충분히 빠르게 돌아갈 수 있다는 것을 알 수 있다.
구현방법은 다양하겠지만, length값을 구한 후 앞에서부터 모든 문자열의 해당 문자가 같은지 확인하면서 다르다면 그 이전까지는 모두 prefix가 같다는 것을 알 수 있다.
"""

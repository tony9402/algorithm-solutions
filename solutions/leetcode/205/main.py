# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/isomorphic-strings/submissions/2076856861
class Solution(object):
    def isIsomorphic(self, s, t):
        # 풀이
        D = defaultdict(str)
        D2 = defaultdict(str)

        for a, b in zip(s, t):
            if D[a] != '' and D[a] != b:
                return False
            D[a] = b

        for a, b in zip(t, s):
            if D2[a] != '' and D2[a] != b:
                return False
            D2[a] = b
        return True


""" Solution Description
앞에서부터 한글자씩 보면서 문자 일대일 매칭이 유지되는지 확인
s에서 t로 바꾸는 과정과 t에서 s로 바꾸는 과정 두 가지를 봐야함.

예를 들어, Example 2에서 s = "f11", t = "b23"를 보면
f는 b로 바뀌고 두 번째 글자 1은 2로 바뀐다. 하지만, 세 번째 문자는 1에서 3으로 바뀌어야 하는데 이미 2로 바뀌었기 때문에 False

근데, 만약 s = "b23", t = "f11"로 들어온다면?
s에서 t로 바꾸는거보면서 확인하면 문제 없다고 판단하여 True라고 생각할 수 있다.
따라서, 일대일 매칭이 되려면 s에서 t로 바꿀 때와 t에서 s로 바꿀 때 둘다 봐야한다.
"""

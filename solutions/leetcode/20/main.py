# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/valid-parentheses/submissions/2063843744
class Solution:
    def isValid(self, s: str) -> bool:
        N = len(s)
        pair = {
            ")": "(",
            "]": "[",
            "}": "{"
        }
        stack = []

        # 스택에 열린괄호를 넣는 과정과 닫힌괄호가 나올 때 처리
        for ch in s:
            if ch in "({[":
                stack.append(ch)
            else:
                # 스택이 비어있다 -> 올바른 괄호 문자열이 아니다.
                if not stack:
                    return False

                # 스택이 비어있지 않은 경우
                if stack[-1] != pair[ch]:
                    return False

                stack.pop()

        return len(stack) == 0


""" Solution Description
"""

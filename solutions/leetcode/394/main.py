# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/decode-string/submissions/2081876941/
class Solution:
    def decodeString(self, s: str) -> str:
        stack = []

        cur_num = 0
        cur_str = ''

        for ch in s:
            if ch == '[':
                stack.append(cur_str)
                stack.append(cur_num)
                cur_num = 0
                cur_str = ''
            elif ch == ']':
                x = stack.pop()
                prev_str = stack.pop()
                cur_str = prev_str + x * cur_str
            elif ch.isdigit():
                cur_num = cur_num * 10 + int(ch)
            else:
                cur_str += ch

        return cur_str


""" Solution Description
숫자는 여러 자리일 수 있으므로 자릿수를 누적하고, 여는 괄호를 만나면 지금까지 만든 문자열과 반복 횟수를 스택에 저장한다.
닫는 괄호에서는 반복 횟수와 이전 문자열을 꺼내 현재 문자열을 반복한 결과와 합친다.
중첩된 괄호는 스택의 후입선출 순서로 자연스럽게 처리된다. 결과 문자열 길이를 R이라고 할 때 시간과 공간 복잡도는 O(R)이다.
"""

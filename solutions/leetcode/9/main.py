# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/palindrome-number/submissions/1163289608
class Solution(object):
    def isPalindrome(self, x):
        return str(x)[::-1] == str(x)
        

""" Solution Description
x값이 음수인 경우 항상 false, x가 양수일 땐 수를 뒤집어서 처음 주어진 x와 값이 같은지 판별.
x를 뒤집을 때 int보다 커질 수 있으므로 타입 주의
"""
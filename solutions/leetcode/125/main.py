# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/valid-palindrome/submissions/2089759085/
class Solution:
    def isPalindrome(self, s: str) -> bool:
        def check(ch):
            if ch.isdigit():
                return ch
            elif ch.isalpha():
                return ch.lower()
            return ''

        N = len(s)
        l, r = 0, N - 1
        flag = True
        while l <= r:
            while l < N and not check(s[l]):
                l += 1
            while r >= 0 and not check(s[r]):
                r -= 1

            if l <= r:
                flag &= check(s[l]) == check(s[r])

            l += 1
            r -= 1
        return flag


""" Solution Description
문자열의 양 끝에 포인터를 두고 영문자나 숫자가 아닌 문자는 건너뛴다.
두 포인터가 가리키는 문자를 소문자로 통일해 비교하고, 모두 같으면 팰린드롬이다.
각 문자를 최대 한 번씩 확인하므로 시간 복잡도는 O(N), 추가 공간 복잡도는 O(1)이다.
"""

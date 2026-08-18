# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/happy-number/submissions/2076873834
class Solution:
    def isHappy(self, n: int) -> bool:

        seen = set()
        seen.add(n)
        while n > 1:
            ret = 0
            while n > 0:
                ret += (n % 10) ** 2
                n //= 10

            if ret in seen:
                return False
            n = ret
            seen.add(n)

        return n == 1


""" Solution Description
문제에 나와있는대로 구현하면 되는 문제이다.
무한루프에 빠진 경우도 확인해야하니 이를 반드시 빠뜨려서는 안된다.
"""

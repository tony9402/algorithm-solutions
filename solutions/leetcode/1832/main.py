# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/check-if-the-sentence-is-pangram/submissions/824321131
class Solution:
    def checkIfPangram(self, sentence: str, chk=0) -> bool:
        return [chk:=chk|1<<(ord(x)-97)for x in sentence]and chk==67108863


""" Solution Description
"""

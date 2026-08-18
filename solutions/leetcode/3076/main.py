# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/shortest-uncommon-substring-in-an-array/submissions/1199076576
class Solution:
    def shortestSubstrings(self, arr: List[str]) -> List[str]:
        ans=[]
        for idx1, x in enumerate(arr):
            found = False
            for k in range(1, len(x) + 1):
                res = "z" * k
                for s in range(0, len(x)):
                    if s + k > len(x):
                        break
                    flag = True
                    for idx2, y in enumerate(arr):
                        if idx1 == idx2: continue
                        if x[s:s+k] in y:
                            flag = False
                            break
                    if flag:
                        if res > x[s:s+k]:
                            res = x[s:s+k]
                        found=True
                if found:
                    ans.append(res)
                    break
            if not found:
                ans.append('')
        return ans


""" Solution Description
"""

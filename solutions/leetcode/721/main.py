# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/accounts-merge/submissions/2100173525/
class Solution:
    def accountsMerge(self, accounts: List[List[str]]) -> List[List[str]]:
        N = len(accounts)
        uf = [i for i in range(N)]

        def find(x: int) -> int:
            while x != uf[x]:
                uf[x] = uf[uf[x]]
                x = uf[x]
            return x

        def merge(u: int, v: int) -> bool:
            u, v = find(u), find(v)
            if u == v:
                return False
            uf[u] = v
            return True

        owner = {}
        for idx, account in enumerate(accounts):
            for email in account[1:]:
                if email in owner:
                    merge(idx, owner[email])
                else:
                    owner[email] = idx

        groups = defaultdict(list)
        for email, x in owner.items():
            groups[find(x)].append(email)

        return [
            [accounts[i][0]] + sorted(emails)
            for i, emails in groups.items()
        ]


""" Solution Description
각 계정을 유니온 파인드의 정점으로 보고, 같은 이메일을 가진 계정들을 하나의 집합으로 합친다.
이메일별로 처음 등장한 계정 인덱스를 기록하면 이후 같은 이메일을 만날 때 두 계정을 연결할 수 있다.
마지막에는 대표 계정별 이메일을 모아 정렬하고 계정 이름을 앞에 붙인다. 이메일 수를 E라고 할 때 합치기는 O(E alpha(N)), 정렬은 전체적으로 O(E log E)이다.
"""

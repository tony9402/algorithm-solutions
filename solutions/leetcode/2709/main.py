# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/greatest-common-divisor-traversal/submissions/1185764396?envType=daily-question&envId=2024-02-25
class Solution:
    def canTraverseAllPairs(self, nums: List[int]) -> bool:
        N = max(nums)
        isPrime = list(range(0, N + 1))
        for i in range(2, (N + 1)):
            if isPrime[i] != i: continue
            for j in range(i ** 2, (N + 1), i): 
                if isPrime[j] == j: isPrime[j] = i

        par, siz = list(range(len(nums) + 1)), [1 for _ in range(len(nums) + 1)]
        def find(x: int) -> int:
            while par[x] != x:
                par[x] = par[par[x]]
                x = par[x]
            return x

        def merge(u: int, v: int) -> int:
            u, v = find(u), find(v)
            if u == v: return
            par[u] = v
            siz[v] += siz[u]
        
        idx = [-1 for _ in range(N + 1)] 
        for i, v in enumerate(nums):
            cur = v
            pre = -1
            while cur != 1:
                p = isPrime[cur]
                cur //= p
                if pre == p:
                    continue
                pre = p
                if idx[p] == -1: idx[p] = i
                else: merge(idx[p], i)
        return siz[find(0)] == len(nums)

""" Solution Description
에라토스테네스의 체를 응용한 버전으로 소인수분해를 해야한다.  
왜냐하면 일반적인 에라토스테네스의 체를 이용해 소수를 다 갖고 있는 다음 N개의 원소를 소인수분해하면 최악의 경우 약 10^9번의 연산을 하므로 TLE가 뜬다.  
x를 소인수분해 할 때 소인수 중 가장 작은 소수를 가지고 있으면 굳이 소수를 다 볼 필요가 없다.  

```
예를 들어, 2434를 소수를 하나씩 보며 소인수분해를 해보자.
먼저, 가장 작은 소수인 2부터 시작하여 나눌 수 있을 때까지 반복한다. 2로 한번 나누어 떨어지므로 1217이 남는다.
그 다음으로 작은 소수 3으로 나누어지는지 확인해본다. 나누어 떨어지지 않으므로 3은 소인수에 포함되지 않는다.  
...
그 다음으로 작은 소수 1213으로 나누어지는지 확인해본다. 나누어 떨어지지 않으므로 1213은 소인수에 포함되지 않는다.  
그 다음으로 작은 소수 1217으로 나누어지는지 확인해본다. 1217로 한번 나누어 떨어지므로 1이 남는다.
```

위처럼 x의 소인수들을 찾으려면 최악의 경우 모든 소수를 탐색해야한다. 수의 최대 값은 10만이므로 소수의 개수는 9592개이다.  
nums 배열 모든 수를 위처럼 소인수 분해한다면 10^5 * 9592 약 10^9 연산을 하므로 TLE가 뜬다.  

그러면 에라토스테네스의 체를 응용한 버전으로 한다면 연산 횟수는 어떻게 될까?  

```
이번에도 2434를 소인수분해해보자.

그 전에 에라토스테네스의 체 응용은 아래와 같이 채워지는 것이다.
number: 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 ... 1217 ... 2434
prime : 2 3 2 5 2 7 2 3  2 11  2 13  2  3  2 17 ... 1217 ...    2

prime은 number를 소인수분해하는데 가장 작은 소수를 의미한다.

2434의 소인수 중 가장 작은 소수가 2이므로 2로 나눈다. 그러면 1217가 남는다.
1217의 소인수 중 가장 작은 소수가 1217이므로 1217로 나눈다. 그러면 1이 남는다.
```

이런식으로 소인수분해를 하니깐 2번만에 소인수분해를 끝낼 수 있다.  
그러면 이 방식의 최악의 경우는 어떻게 될까? 소인수가 가장 많은 수를 소인수분해할때가 가장 최악일 것이다.  
그러므로 수의 범위가 10^5일때는 약 2^16가 가장 소인수가 많으므로 최악의 경우 연산횟수는 16번이다.  
이런식으로 소인수분해를 하면 매우 빠르게 소인수 분해를 할 수 있다.  
연습문제 : https://www.acmicpc.net/problem/16563


nums 배열을 아래 순서대로 진행하면 된다.  
1. 현재 x의 소인수들을 확인하여 각 소수가 이전에 등장한 수의 소인수인지 확인 후 그 수와 합친다.
2. 모든 배열을 순회한 후 합쳐진 크기가 nums 길이와 동일하면 true 아니면 false를 리턴하면 된다.
"""
# Authored by : parksb08
# Co-authored by : -
# Link : http://boj.kr/467d3ad526dc460db851f8774d4f86b7
import sys
def input():
    return sys.stdin.readline().rstrip()

inputs = input()
rs=[]
stack=[]
i_p={'+':1,'-':1,'*':2,'/':2, '(':4, ')':0} #stack에 들어갈 때
s_p={'+':1,'-':1,'*':2,'/':2, '(':0} #stcak에서 나올 때
for i in inputs:
    if i.isalpha():
        rs.append(i)
    elif i == '(':
        stack.append(i)
    elif i ==')':
        if stack:
            while s_p[stack[-1]] >= i_p[i]:
                if stack[-1]=='(':
                    stack.pop()
                    break
                else:
                    rs.append(stack.pop())
                if not stack:
                    break
    else:
        if stack:
            while s_p[stack[-1]] >= i_p[i]:
                rs.append(stack.pop())
                if not stack:
                    break
        stack.append(i)
while stack:
    rs.append(stack.pop())

print(''.join(rs))
'''
후위표기식을 만드는 문제
스택을 이용해서 풀었다.
1. 알파벳이면 결과에 바로 추가
2. 여는 괄호면 스택에 추가
3. 닫는 괄호면 여는 괄호가 나올 때 까지 스택에서 pop
4. 연산자면 스택에서 우선순위가 높은 연산자가 나올 때 까지 pop
5. 스택이 빌 때 까지 pop
6. 결과 출력
'''

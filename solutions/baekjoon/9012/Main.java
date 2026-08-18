// Authored by : semInDev
// Co-authored by : -
// Link : http://boj.kr/24bfbbc5ff394c54b1d51d7ed1bca763

import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args) throws IOException {
        FastReader input = new FastReader();
        
		int T = input.nextInt();
		
		Stack<Character> stack;
		StringBuilder sb = new StringBuilder();
		while(T-->0) {
			boolean tf = true;
			String str = input.next();
			stack = new Stack<>();
			
			for(int i=0; i<str.length(); i++) {
				char c = str.charAt(i);
				
				if(c == '(') stack.push('(');
				else {
					if(stack.isEmpty()) { // ex. ()))의 경우
						sb.append("NO\n");
						tf = false;
						break;
					}
					else stack.pop();
				}
			}
			
			if(tf) {//tf가 없으면 ()))의 경우에 NO\nYES\n이라고 출력됨.
				if(stack.isEmpty()) sb.append("YES\n"); // ex.(()의 경우
				else sb.append("NO\n");
			}
			
		}
		System.out.print(sb);
	}
	
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() throws IOException{
        	br = new BufferedReader(new InputStreamReader(System.in)); //백준 제출 시 주석해제를 하면 됩니다.
        	// br = new BufferedReader(new FileReader("input.txt")); //IDE 실행 시 주석해제를 하면 됩니다.
        }

        String next() {
            while(st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                }
                catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() { return Integer.parseInt(next()); }
        long nextLong() { return Long.parseLong(next()); }
        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            }
            catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }
}

/* Solution Description
	
	1. java 컬렉션 프레임워크의 Stack을 사용하여
	(에는 push를, )에는 pop을 진행함으로써 괄호 짝을 맞춰갈 수 있다.
	
	2. NO가 발생하는 상황은 크게 두 가지로 나눠볼 수 있다.
		1) (()와 같이 스택에서 이미 모든 문자에 charAt을 진행한 후에도 (가 스택에 남아있는 경우.
		2) ())))와 같이 스택에서 이미 stack.isEmpty의 상황에서도 )를 계속 부르는 경우.
	
 */

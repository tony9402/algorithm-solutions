// Authored by : semInDev
// Co-authored by : -
// Link : https://www.acmicpc.net/problem/18258

import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args) throws IOException {
        FastReader input = new FastReader();
        
        Deque<Integer> deque = new ArrayDeque<>(); // back명령어를 사용하기 위해 deque이용
        StringBuilder sb = new StringBuilder();
        
        int N = input.nextInt();
		while(N-->0) {
			String cmd = input.next();			
			switch (cmd) {
				case "push":
					int X = input.nextInt();
					deque.add(X);
					break;
				case "pop":
					if(deque.isEmpty()) sb.append(-1+"\n");
					else sb.append(deque.poll()+"\n");
					break;
				case "size":
					sb.append(deque.size()+"\n");
					break;
				case "empty":
					if(deque.isEmpty()) sb.append(1+"\n");
					else sb.append(0+"\n");
					break;
				case "front":
					if(deque.isEmpty()) sb.append(-1+"\n");
					else sb.append(deque.peekFirst()+"\n");
					break;
				case "back":
					if(deque.isEmpty()) sb.append(-1+"\n");
					else sb.append(deque.peekLast()+"\n");
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
	1. 큐를 단순히 구현할 수 있지만, 이는 라이브코테에서 요구되는 방식이라고 판단하여
	'빠르게' 풀어야 하는 코딩테스트에서는 java의 컬렉션 프레임워크를 사용하는 것이 적절하다고 판단했다.
	2. 문제 제목은 queue지만, 뒤에서 peek하는 과정인 'back'을 요구하여 deque를 사용했다.
	3. 또한, 가독성을 위하여 cmd.equals("push")를 if문으로 나열하기보다는
	switch를 활용했다.
 */
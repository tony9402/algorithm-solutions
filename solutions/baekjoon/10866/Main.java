// Authored by : semInDev
// Co-authored by : -
// Link : https://www.acmicpc.net/problem/10866

import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args)throws IOException{
		FastReader input = new FastReader();
		StringBuilder sb = new StringBuilder();
		
		int N = input.nextInt();
		ArrayDeque<Integer> deque = new ArrayDeque<>();
		while(N-->0) {
			String cmd = input.next();
			switch(cmd) {
				case "push_front":
					deque.addFirst(input.nextInt());
					break;
					
				case "push_back":
					deque.addLast(input.nextInt());
					break;
					
				case "pop_front":
					if(deque.isEmpty()) sb.append(-1+"\n");
					else sb.append(deque.pollFirst()+"\n");
					break;
					
				case "pop_back":
					if(deque.isEmpty()) sb.append(-1+"\n");
					else sb.append(deque.pollLast()+"\n");
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
	
	- java 컬렉션 프레임워크의 ArrayDeque을 사용하여 덱을 풀 수 있다.
	
 */
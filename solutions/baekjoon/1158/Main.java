// Authored by : semInDev
// Co-authored by : -
// Link : https://www.acmicpc.net/problem/1158

import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args)throws IOException{
		FastReader input = new FastReader();
		
		int N = input.nextInt();
		int K = input.nextInt();
		
		StringBuilder sb = new StringBuilder();
		sb.append("<");
		
		Queue<Integer> queue = new ArrayDeque<>();
		for(int i=1; i<N+1; i++) { // 초기값
			queue.add(i);
		}
		
		while(queue.size()!=1) {
			for(int i=0; i<K-1; i++) { // K-1번째까지 poll하지 않고 넘어감
				int temp = queue.poll();
				queue.add(temp);
			}
			sb.append(queue.poll() + ", "); // K번째는 poll
		}
		sb.append(queue.poll()+">");
		
		System.out.println(sb);
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
	
	- java 컬렉션 프레임워크의 Queue(ArrayDeque로 구현)를 사용한다.
	원형으로 앉은 사람들을 순서대로 카운트하는 것을 큐를 통해 구현할 수 있다.
	
 */
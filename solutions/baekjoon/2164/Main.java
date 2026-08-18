// Authored by : semInDev
// Co-authored by : -
// Link : http://boj.kr/1d389a25667249adb06ff3605abe25b0

import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args)throws IOException{
		FastReader input = new FastReader();
		int N = input.nextInt();
		
		Queue<Integer> queue = new ArrayDeque<>();
		for(int i=1; i<N+1; i++) { // queue 초기화
			queue.add(i);
		}
		
		while(queue.size() != 1) {
			queue.poll(); // 맨 위 카드 하나 버리기
			
			int temp = queue.poll(); // 맨 위 카드 하나 아래로 넣기
			queue.add(temp);
		}
		
		System.out.println(queue.poll());
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
	쌓아놓은 카드의 윗부분을 큐의 front 쪽, 아래를 back 쪽이라고 둔다.
	
 */

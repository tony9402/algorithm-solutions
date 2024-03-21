// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/ba18fecb890044edba3c787ce936357d
import java.util.*;
import java.io.*;

public class Main{
	public static void main(String[] args) {
        FastReader rd = new FastReader();

        int N = rd.nextInt();

        PriorityQueue<int[]> pq1 = new PriorityQueue<>((n1, n2) -> {
            if (n1[0] == n2[0]) return n1[1] - n2[1];
            return n1[0] - n2[0];
        });    

		for (int i = 0; i < N; i++) {
			pq1.add(new int[]{rd.nextInt(), rd.nextInt()});
		}

        PriorityQueue<Integer> pq2 = new PriorityQueue<>();
		pq2.add(pq1.poll()[1]);
		int ans = 1;
		while (!pq1.isEmpty()) {
			int[] curr = pq1.poll();

			if (pq2.peek() <= curr[0]) pq2.poll();
			pq2.add(curr[1]);

			ans = Math.max(ans, pq2.size());
		}

        System.out.println(ans);
	}

    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
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
        double nextDouble() { return Double.parseDouble(next()); }
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
1. 스위핑의 응용문제. 보통 스위핑 문제는 범위의 총 비용을 구하거나, 
   겹치는 횟수가 몇개 인지를 확인하는 문제가 많이 나오는 듯 하다. 이번 문제는 후자의 경우이다.

2. 우선순위 큐 `pq2` 를 활용하여 선분이 겹치는 갯수를 확인할 수 있다. 
   시작점을 기준으로 정렬된 입력값에 대해, 매 탐색 시 `pq2`에 선분의 종료값을 담는다. 

3. 임의의 입력에 대해 `pq2`에 담아둔 선분의 종료값 보다 임의의 시작값이 같거나 큰 경우, 
   해당 종료 선분의 영역을 재사용할 수 있음을 의미한다. 
   이 조건이 만족한다면 `pq2` 의 선분의 종료값을 빼주자. 
   추후 현재 입력의 종료값이 들어가 그 범위를 재사용된다.

4. 선분이 겹치는 최대 갯수는 각 탐색마다 `pq2` 의 최대 사이즈가 된다.
*/

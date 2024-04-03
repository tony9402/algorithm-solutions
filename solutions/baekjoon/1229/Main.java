// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/7aa1cbf4fecc4f928327f2786fa1da53

import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		FastReader rd = new FastReader();
		int N = rd.nextInt();

		List<Integer> list = new ArrayList<>();

		// 육각수 만들기
		list.add(1);
		int sum = 5;
		while (list.get(list.size() - 1) + sum <= N) {
			list.add(list.get(list.size() - 1) + sum);
			sum += 4;
		}


		int dp[] = new int[N + 1];
		for (int i = 1; i <= N; i++) {
			dp[i] = 6;
			for (int s : list) {
				if (s > i) break;
				dp[i] = Math.min(dp[i], dp[i - s] + 1);
			}
		}

		System.out.println(dp[N]);
	}

	static class FastReader {
		BufferedReader br;
		StringTokenizer st;

		public FastReader() {
			br = new BufferedReader(new InputStreamReader(System.in));
		}

		String next() {
			while (st == null || !st.hasMoreElements()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			return st.nextToken();
		}

		int nextInt() {
			return Integer.parseInt(next());
		}

		long nextLong() {
			return Long.parseLong(next());
		}

		double nextDouble() {
			return Double.parseDouble(next());
		}

		String nextLine() {
			String str = "";
			try {
				str = br.readLine();
			} catch (IOException e) {
				e.printStackTrace();
			}
			return str;
		}
	}
}

/* Solution Description

1. 냅색 응용 문제. `N` 만큼의 육각수를 만든 후, 
   이를 기반으로 냅색을 통해 문제를 해결할 수 있다.

2. 육각수는 결국, 육각형 중 2개의 선분을 모형이다. 
   즉, 임의의 육각수의 크기를 $h_n$ 이라 가정한다면, 
   현재 육각수의 크기는 $h_{n-1}$ + 나머지 4개 선분의 점의 갯수가 된다. 

3. $n$ 이 커질수록 선분 별로 1개씩 점이 추가되므로, 
   $h_1$ 의 4개 선분의 점의 갯수인 `5` 를 시작으로 4씩 추가해가며 육각수의 크기를 구할 수 있다.

4. 이후 냅색을 통해 `dp[N]` 의 최솟값을 구하면 된다.

 */
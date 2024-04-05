// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/9b1dc9632bd749358f38832c1d34704a

import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		FastReader rd = new FastReader();
		int N = rd.nextInt();

		int[][] a1 = new int[N][N];
		int[][] a2 = new int[N][N];

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				a1[i][j] = rd.nextInt();
				a2[i][j] = a1[i][j];
			}
		}

		for (int k = 0; k < N; k++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (i == j || j == k || k == i) continue;

					if (a1[i][j] > a1[i][k] + a1[k][j]) {
						System.out.println(-1);
						return;
					}

					if (a1[i][j] == a1[i][k] + a1[k][j]) {
						a2[i][j] = 0;
					}
				}
			}
		}

		int sum = 0;
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				sum += a2[i][j];
			}
		}
		System.out.println(sum);
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

1. 플로이드-워셜 응용 문제. 최단 경로의 결과가 입력 값으로 주어지고, 이를 기반으로 본래 사용된 간선을 확인한다.

2. 플로이드-워셜의 핵심은 현재 간선 비용보다 우회하여 오는 간선의 비용이 더 적은 경우 업데이트를 하는 것이다. 
   따라서 우회한 간선의 합이 현재의 간선 비용과 동일하다면, 우회한 간선 쪽을 반영한 것이라고 추론할 수 있다.

3. 우회한 간선이 반영된 경우를 `0` 으로 변경하자. 
   모든 탐색이 끝난 이후에도 `0` 이 아닌 간선이 본래 최단 경로를 결과를 찾기 위해 사용된 초기 간선이 된다. 

4. 탐색 시, 현재 간선보다 우회한 간선의 합이 더 큰 경우, 
   최단 경로를 잘못 파악한 것으로 간주하고 `-1` 을 출력한다.

 */
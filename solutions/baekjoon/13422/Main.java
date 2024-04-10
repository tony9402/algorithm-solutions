// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/e160208f4a324b34b406ca253ca6194f

import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		FastReader rd = new FastReader();
		int T = rd.nextInt();

		StringBuffer sb = new StringBuffer();
		while (--T >= 0) {
			int N = rd.nextInt();
			int M = rd.nextInt();
			int K = rd.nextInt();

			int a[] = new int[N + M];

			for (int i = 1; i <= N; i++) {
				a[i] = a[i - 1] + rd.nextInt();
			}

			if (N == M) {
				sb.append(a[N] < K ? 1 : 0).append("\n");
				continue;
			}

			int idx = N + 1;
			for (int i = 1; i < M; i++) {
				a[idx] = a[idx - 1] + a[i] - a[i - 1];
				idx++;
			}

			int ret = 0;
			for (int i = 0; i < N; i++) {
				if (a[i + M] - a[i] < K) ret++;
			}
			sb.append(ret).append("\n");
		}
		System.out.print(sb.toString());
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

1. 누적합을 활용한 문제. 특정 조건이 존재하므로,
   여러 테스트 케이스를 반영해보지 않으면, 맞왜틀에 빠질 수 있는 문제이다.

2. 입력값을 기준으로 누적합을 구한후, 누적합의 차를 활용하여 연속되는 집의 갯수 `M` 의 합계를 구한다.
   단, 마을의 집은 처음의 집과 마지막 집이 이어지기 때문에 `M-1` 개 만큼, 입력 후반 부에서 처음의 집을 지나는 누적합을 추가적으로 구했다.

3. 입력의 제한사항을 `M<=N`으로 `N`과 `M` 이 서로 동일할 수 있다.
   `N` 과 `M` 이 동일한 경우에는 누적합의 차가 항시 동일하기 때문에, `N` 만큼의 탐색동안 중복된 카운트가 반영될 수 있다.

4. 위의 조건 외에는 누적합 간 `M` 범위의 차를 통해 돈을 훔치는 방법의 가짓수를 구할 수 있다.

 */
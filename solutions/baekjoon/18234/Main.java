// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/62c1d082296c42ad9a696c131a5a6314

import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		FastReader rd = new FastReader();
		int N = rd.nextInt();
		int T = rd.nextInt();
		int a[][] = new int[N][2];

		for (int i = 0; i < N; i++) {
			a[i][0] = rd.nextInt();
			a[i][1] = rd.nextInt();
		}

		Arrays.sort(a, (n1, n2) -> {
			if (n1[1] == n2[1]) return n2[0] - n1[0];
			return n2[1] - n1[1];
		});

		int day = 1;
		long sum = 0;
		for (int i = 0; i < N; i++) {
			sum += 1L * a[i][1] * (T - day++) + a[i][0];
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

1. 정렬 응용 문제. 주어진 문제의 조건에 대해 수학적 명제를 도출할 수 있다면 손쉽게 풀 수 있는 문제이다.

2. 문제에서 유심히 지켜봐야할 부분은 $**p_i$ 항상 $w_i$ 이상의 값을 가진다는 점이다.**
   즉 영양제 투입 횟수가 많아질수록 $p_i$ 가 큰 당근의 맛이 더 맛있어 질 수 밖에 없으며,
   영양제를 가장 많이 투입되었을 때 까지 기다렸다가 먹는 것이 맛의 합이 가장 크다.

3. 당근이 심어지는 첫째날을 제외하면, $p_i$ 투입 횟수가 최대로 적용되는 경우는 $T-1$ 번이다.
   따라서 $p_i$ 를 기준으로 내림차순 정렬을 진행한 후, 다음의 계산식을 통해 문제를 해결할 수 있다.

    $result = w_i + (T-d)*p_i$

4. 정답 결과는 `int` 를 초과하므로, 처음부터 입력값을 `long` 으로 받거나, 누적 값 계산 시 타입 캐스팅을 적용하자.


 */

// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/6c68b4d99ce3457a948740d3a30d4799

import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		FastReader rd = new FastReader();
		int N = rd.nextInt();
		int a1[] = new int[N];
		int a2[] = new int[N];

		// 0
		for (int i = 0; i < a1.length; i++) {
			a1[i] = rd.nextInt();
		}


		// a1 -> a2 만들기
		int ret = 0;
		while (!check(a1, a2)) {
			// 홀수가 있는지 확인
			boolean check = false;
			for (int i = 0; i < N; i++) {
				if (a1[i] % 2 == 1) {
					check = true;
					a1[i]--;
					ret++;
				}
			}

			// 다 짝수라면?
			if (!check) {
				for (int i = 0; i < N; i++) {
					a1[i] /= 2;
				}
				ret++;
			}
		}
		System.out.println(ret);
	}

	private static boolean check(int[] a1, int[] a2) {
		for (int i = 0; i < a1.length; i++) {
			if (a1[i] != a2[i]) return false;
		}
		return true;
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

1. 고민이 필요한 문제. `A → B` 로 변화시키는 것이 아닌 `B → A` 로 바꾼다는 생각의 전환이 필요하다.

2. **베열에 있는 모든 값을 두 배 시킨다** 는 연산은 결국 배열의 모든 값이 **짝수**가 됨을 의미한다.
   따라서 B → A로 전향할 때는, 홀수가 있는지 확인하고 홀수가 있다면 `-1` 차감하여 짝수로 만들어주고,
   `B` 의 모든 값이 짝수인 경우에만 `2` 로 나눠주는 것으로 최소 횟수로 `B` 를 `A` 로 만드는 것이 가능하다.

 */

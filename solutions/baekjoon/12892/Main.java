// Authored by: beberiche
// Co-authored by: http://boj.kr/1e4c33777da24f94981b6b6062e2fbb6
// Link:

import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		FastReader rd = new FastReader();

		int N = rd.nextInt();
		int D = rd.nextInt();
		int a[][] = new int[N][2];


		for (int i = 0; i < N; i++) {
			a[i][0] = rd.nextInt();
			a[i][1] = rd.nextInt();
		}

		Arrays.sort(a, (n1, n2) -> n1[0] - n2[0]);

		int st = 0;
		int ed = 0;
		long ans = 0;
		long curr = 0;

		while (ed < N) {
			int diff = a[ed][0] - a[st][0];

			if (diff < D) {
				curr += a[ed][1];
				ans = Math.max(ans, curr);
				ed++;
			} else {
				curr -= a[st][1];
				st++;
			}
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

1. 투포인터 기초 문제. 선물의 가격이 `D` 이상 차이나지 않는 만족도의 최대합을 구해야한다.

2. 임의의 선물 범위가 `D` 이상 차이가 나지 않는다 것은,
   곧 해당 범위의 최대 선물 가격과 최소 선물 가격이 `D` 를 넘기지만 않는다면
   해당 범위의 선물들은 모두 총 만족도에 반영할 수 있다는 것을 의미한다.

3. 따라서, 주어진 입력을 선물 가격으로 오름차순 정렬한 후,
   `st, ed` 모두 `0` 을 시작으로 매 탐색마다,
   현재 `st,ed` 인덱스의 선물 가격 차이가 `D` 보다 작다면 `ed` 를 높이고,
   그렇지 않은 경우에는 `st` 를 높였다.

 */
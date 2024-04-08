// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/a194b1386c8a4767aac779c171d0d2f1

import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		FastReader rd = new FastReader();
		int N = rd.nextInt();
		int[] a = new int[N + 1];
		for (int i = 1; i <= N; i++) {
			a[i] = rd.nextInt();
		}
		int h = (int) Math.ceil(Math.log(N) / Math.log(2));
		int size = 1 << (h + 1);
		int[] tree_odd = new int[size];
		int[] tree_even = new int[size];

		init(1, 1, N, a, tree_odd, tree_even);

		int M = rd.nextInt();

		StringBuffer sb = new StringBuffer();
		for (int i = 0; i < M; i++) {
			int cmd = rd.nextInt();
			int n1 = rd.nextInt();
			int n2 = rd.nextInt();

			if (cmd == 1) {
				update(1, 1, N, n1, n2, tree_odd, tree_even);
			} else if (cmd == 2) {
				sb.append(query(1, 1, N, n1, n2, tree_odd, tree_even, true)).append("\n");
			} else {
				sb.append(query(1, 1, N, n1, n2, tree_odd, tree_even, false)).append("\n");
			}
		}
		System.out.print(sb.toString());
	}


	private static void init(int curr, int st, int ed, int[] a, int[] tree_odd, int[] tree_even) {
		if (st == ed) {
			if (a[st] % 2 == 1) {
				tree_odd[curr] = 1;
			} else {
				tree_even[curr] = 1;
			}
			return;
		}

		int mid = (st + ed) / 2;
		init(curr * 2, st, mid, a, tree_odd, tree_even);
		init(curr * 2 + 1, mid + 1, ed, a, tree_odd, tree_even);
		tree_odd[curr] = tree_odd[curr * 2] + tree_odd[curr * 2 + 1];
		tree_even[curr] = tree_even[curr * 2] + tree_even[curr * 2 + 1];
	}

	private static void update(int curr, int st, int ed, int idx, int newVal, int[] tree_odd, int[] tree_even) {
		if (idx < st || ed < idx) {
			return;
		}

		if (st == ed) {
			tree_even[curr] = newVal % 2 == 0 ? 1 : 0;
			tree_odd[curr] = newVal % 2 == 1 ? 1 : 0;
			return;
		}

		int mid = (st + ed) / 2;
		update(curr * 2, st, mid, idx, newVal, tree_odd, tree_even);
		update(curr * 2 + 1, mid + 1, ed, idx, newVal, tree_odd, tree_even);
		tree_odd[curr] = tree_odd[curr * 2] + tree_odd[curr * 2 + 1];
		tree_even[curr] = tree_even[curr * 2] + tree_even[curr * 2 + 1];
	}

	private static int query(int curr, int st, int ed, int l, int r, int[] tree_odd, int[] tree_even, boolean check) {
		if (r < st || ed < l) {
			return 0;
		}


		if (l <= st && ed <= r) {
			if (check) return tree_even[curr];
			else return tree_odd[curr];
		}


		int mid = (st + ed) / 2;
		int ret1 = query(curr * 2, st, mid, l, r, tree_odd, tree_even, check);
		int ret2 = query(curr * 2 + 1, mid + 1, ed, l, r, tree_odd, tree_even, check);
		return ret1 + ret2;
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

	1. 세그먼트 트리 기본 문제. `tree[]` 를 2개 만들어, 
       임의의 범위에 대한 짝수, 홀수인 경우의 갯수를 따로 구한다.

 */


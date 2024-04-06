// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/232b374fbc5843168b5c39b49d8ba7c9

import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		FastReader rd = new FastReader();

		while (rd.hasMoreLine()) {
			int N = rd.nextInt();
			int M = rd.nextInt();

			int a[] = new int[N + 1];
			for (int i = 1; i <= N; i++) {
				int num = rd.nextInt();
				if (num > 0) a[i] = 1;
				else if (num < 0) a[i] = -1;
			}

			int h = (int) Math.ceil((Math.log(N) / Math.log(2)));
			int tree[] = new int[1 << (h + 1)];
			init(tree, a, 1, 1, N);

			for (int i = 0; i < M; i++) {
				String cmd = rd.next();
				int n1 = rd.nextInt();
				int n2 = rd.nextInt();

				if (cmd.equals("C")) {
					if (n2 > 0) n2 = 1;
					else if (n2 < 0) n2 = -1;
					else n2 = 0;
					update(tree, 1, 1, N, n1, n2);
				} else {
					int ret = query(tree, 1, 1, N, n1, n2);
					if (ret < 0) {
						System.out.print("-");
					} else if (ret == 0) {
						System.out.print(0);
					} else {
						System.out.print("+");
					}
				}
			}
			System.out.println();
		}

	}

	private static int query(int[] tree, int idx, int st, int ed, int l, int r) {
		if (r < st || l > ed) {
			return 1;
		}

		if (l <= st && ed <= r) {
			return tree[idx];
		}

		int mid = (st + ed) >> 1;
		int left = query(tree, idx * 2, st, mid, l, r);
		int right = query(tree, idx * 2 + 1, mid + 1, ed, l, r);
		return left * right;
	}

	private static void update(int[] tree, int idx, int st, int ed, int curr_idx, int val) {
		if (curr_idx < st || ed < curr_idx) {
			return;
		}

		if (st == ed) {
			tree[idx] = val;
			return;
		}

		int mid = (st + ed) >> 1;
		update(tree, idx * 2, st, mid, curr_idx, val);
		update(tree, idx * 2 + 1, mid + 1, ed, curr_idx, val);
		tree[idx] = tree[idx * 2] * tree[idx * 2 + 1];
	}

	private static void init(int[] tree, int[] a, int idx, int st, int ed) {
		if (st == ed) {
			tree[idx] = a[st];
			return;
		}

		int mid = (st + ed) >> 1;
		init(tree, a, idx * 2, st, mid);
		init(tree, a, idx * 2 + 1, mid + 1, ed);
		tree[idx] = tree[idx * 2] * tree[idx * 2 + 1];
	}

	static class FastReader {
		BufferedReader br;
		StringTokenizer st;

		public FastReader() {
			br = new BufferedReader(new InputStreamReader(System.in));
		}

		boolean hasMoreLine() {
			String str;
			try {
				if ((str = br.readLine()) != null) {
					st = new StringTokenizer(str);
					return true;
				}
				throw new IOException();
			} catch (IOException e) {
				return false;
			}
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

1. 세그먼트 트리 응용문제. 출력값을 기준으로 산출과정을 어떻게 도출할 것인지 고민이 필요하다.

2. 이 문제의 경우, 입력값을 기준으로 이루어지는 최대 곱은 $100^{100000}$ 이므로, 단순 곱셈 연산으로는 문제를 해결하기 어렵다.

3. 출력값을 미루어볼 때 해당 수의 크기와는 상관없이 양수인지, 음수인지, `0` 인지만 판별하면 된다.
   따라서, 주어진 값을 `-1, 0, 1` 로 치환하여 계산하면 타입의 최대를 넘지 않은 체 문제를 해결할 수 있다.

 */


// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/8c50b80a0a1e4770bc020aa0d114fcd8

import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		FastReader rd = new FastReader();
		int N = rd.nextInt();
		int M = rd.nextInt();

		List<int[]> list[] = new ArrayList[N + 1];
		for (int i = 1; i <= N; i++) {
			list[i] = new ArrayList<>();
		}

		for (int i = 0; i < M; i++) {
			int a = rd.nextInt();
			int b = rd.nextInt();
			int c = rd.nextInt();

			list[a].add(new int[]{b, c});
			list[b].add(new int[]{a, c});
		}

		int st = rd.nextInt();
		int ed = rd.nextInt();

		PriorityQueue<int[]> pq = new PriorityQueue<>((n1, n2) -> n1[1] - n2[1]);
		int[] dist = new int[N + 1];
		int INF = (int) 1e9;
		Arrays.fill(dist, INF);
		pq.add(new int[]{st, 0});
		dist[st] = 0;

		while (!pq.isEmpty()) {
			int[] curr = pq.poll();

			if (curr[0] == ed) break;

			for (int[] next : list[curr[0]]) {
				if (dist[next[0]] > curr[1] + next[1]) {
					dist[next[0]] = curr[1] + next[1];
					pq.add(new int[]{next[0], dist[next[0]]});
				}
			}
		}

		System.out.println(dist[ed]);
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

1. 다익스트라 기본 문제. 문제의 내용 그대로 임의의 지점 `s->t` 까지의 최단 경로를 구하는 문제이다.

2. 양방향의 인접 리스트과 `dist[]` 을 생성하여,
   우선순위 큐를 이용해 `s` 를 시작으로 `t` 까지 도달하기까지 최소 거리를 갱신한다.

 */

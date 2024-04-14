// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/f6965f3f15f04d6db896babd4720c86e

import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		FastReader rd = new FastReader();
		int N = rd.nextInt();
		int M = rd.nextInt();

		int[] a = new int[N];
		for (int i = 0; i < N; i++) {
			a[i] = rd.nextInt();
		}

		List<Node> list[] = new ArrayList[N];
		for (int i = 0; i < N; i++) {
			list[i] = new ArrayList<>();
		}

		for (int i = 0; i < M; i++) {
			int n1 = rd.nextInt();
			int n2 = rd.nextInt();
			int dist = rd.nextInt();

			boolean check1 = check(n1, a);
			boolean check2 = check(n2, a);

			if (check1 && check2) {
				list[n1].add(new Node(n2, dist));
				list[n2].add(new Node(n1, dist));
			}
		}

		long[] dist = new long[N];
		long INF = (long) 3e11 + 4;
		Arrays.fill(dist, INF);
		dist[0] = 0;

		PriorityQueue<Node> pq = new PriorityQueue<>();
		pq.add(new Node(0, 0));
		while (!pq.isEmpty()) {
			Node curr = pq.poll();

			if (dist[curr.id] < curr.dist) continue;

			for (Node next : list[curr.id]) {
				if (dist[next.id] > curr.dist + next.dist) {
					dist[next.id] = curr.dist + next.dist;
					pq.add(new Node(next.id, dist[next.id]));
				}
			}
		}

//		System.out.println(-1);
		long ans = dist[N - 1] == INF ? -1 : dist[N - 1];
		System.out.println(ans);
	}

	private static boolean check(int node, int[] a) {
		return node == a.length - 1 || a[node] == 0;
	}

	private static class Node implements Comparable<Node> {
		int id;
		long dist;


		Node(int id, long dist) {
			this.id = id;
			this.dist = dist;
		}

		@Override
		public int compareTo(Node o) {
			return Long.compare(this.dist, o.dist);
		}
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

1. 다익스트라 응용 문제. 일반적인 다익스트라 치고 간선의 수, 비용의 최대치가 꽤 큰 편이다.
   이를 최적화 할 수 있는 식이 필요한 문제이다.

2. 결과적으로 유섭이가 백도어에 성공하기 위해서는, 넥서스 외에 시야가 보이는 거점을 지나쳐서는 안된다.
   따라서, 그래프를 형성할 때, 주어지는 입력값의 거점이 **넥서스가 아님에도, 상대의 시야에 보이는 거점** 이라면 그래프 연결에 제외하도록 했다.

3. 더불어, `dist[]`  내에 저장된 임의의 노드 `i` 에 대한 최단 비용보다,
   탐색 시의 `dist` 비용이 더 크다면 다음 탐색을 하는 방법으로 탐색 시간을 줄였다.

 */

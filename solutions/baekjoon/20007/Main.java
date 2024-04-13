// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/fd94d245b5254d968a6f7518f865977d

import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		FastReader rd = new FastReader();
		int N = rd.nextInt();
		int M = rd.nextInt();
		int X = rd.nextInt();
		int Y = rd.nextInt();


		int INF = (int) 1e7 + 4;
		int[] dist = new int[N];
		Arrays.fill(dist, INF);


		List<int[]> list[] = new ArrayList[N];
		for (int i = 0; i < N; i++) {
			list[i] = new ArrayList<>();
		}

		for (int i = 0; i < M; i++) {
			int n1 = rd.nextInt();
			int n2 = rd.nextInt();
			int d = rd.nextInt();
			list[n1].add(new int[]{n2, d});
			list[n2].add(new int[]{n1, d});
		}

		PriorityQueue<int[]> pq = new PriorityQueue<>((n1, n2) -> n1[1] - n2[1]);
		pq.add(new int[]{Y, 0});
		dist[Y] = 0;

		while (!pq.isEmpty()) {
			int[] curr = pq.poll();

			for (int[] next : list[curr[0]]) {
				if (dist[next[0]] > curr[1] + next[1]) {
					dist[next[0]] = curr[1] + next[1];
					pq.add(new int[]{next[0], dist[next[0]]});
				}
			}
		}

		Arrays.sort(dist);
		int sum = 0;
		int ans = 1;
		for (int i = 0; i < dist.length; i++) {
			if (dist[i] * 2 > X) {
				ans = -1;
				break;
			}

			sum += dist[i] * 2;
			if (sum > X) {
				sum = dist[i] * 2;
				ans++;
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

1. 다익스트라 응용 문제. 떡은 한번에 하나만 들고 갈 수 있다는 점에 근거하여,
   임의의 집에 떡을 돌리는 비용은해당 집까지 걸리는 `최단 경로 비용 * 2` 가 된다.

2. 이웃 집을 모두 방문하기 위해서는 다음과 같은 조건이 명시되어야 한다.
    - 이웃 집까지의 `최단 경로 비용 * 2` 가 `X` 이내로 가능한 거리인가?
    - `Y` 를 시작점으로 했을 때, `N-1` 개의 모든 이웃집은 연결되어 있는가?

3. `Y` 를 시작점으로 하여, 모든 이웃 집간의 최단 경로를 구한다. 이후, 오름차순 정렬을 하여, `최단 경로 비용 * 2` 를 누적한다.
    누적한 값이 아직 `X` 를 넘지 않는다면 연속으로 갈 수 있는 거리이며, 그게 아니라면 다음날에 방문해야한다.

 */
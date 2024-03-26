// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/31e42a2bdaed47a2a5d2c854c87366c8

import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		FastReader rd = new FastReader();

		int N = rd.nextInt();
		int S = rd.nextInt();

		Car a[] = new Car[N];
		for (int i = 0; i < N; i++) {
			a[i] = new Car();
			a[i].id = i;
			a[i].pos = rd.nextInt();
		}

		for (int i = 0; i < N; i++) {
			a[i].cost = rd.nextInt();
		}

		Arrays.sort(a);

		Queue<Integer> q = new LinkedList<>();
		boolean visited[] = new boolean[N];

		for (int i = 0; i < N; i++) {
			if (a[i].id == S - 1) {
				q.add(i);
				visited[i] = true;
				break;
			}
		}


		while (!q.isEmpty()) {
			int idx = q.poll();

			for (int i = idx - 1; i >= 0; i--) {
				if (a[idx].pos - a[idx].cost > a[i].pos) {
					break;
				}

				if (visited[i]) continue;

				visited[i] = true;
				q.add(i);
			}


			for (int i = idx + 1; i < N; i++) {
				if (a[idx].pos + a[idx].cost < a[i].pos) {
					break;
				}

				if (visited[i]) continue;

				visited[i] = true;
				q.add(i);
			}
		}


		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < N; i++) {
			if (visited[i]) sb.append(i + 1).append(" ");
		}

		System.out.print(sb.toString());
	}

	static class Car implements Comparable<Car> {
		int id;
		int pos;
		int cost;

		@Override
		public int compareTo(Car o) {
			return this.pos - o.pos;
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

1. BFS 응용 문제. 주어진 시작 위치에서 연료 값으로 도달할 수 있는 차들을 파악해야한다.
주어진 `N` 의 최댓값은 `1e6` 이며, 단순 `BFS` 의 경우 최악의 시간복잡도를 반영했을 때 `TLE` 가 발생할 것이다. 

2. 이를 개선하기 위해, 모든 차의 정보를 시작위치로 정렬하자. 
이 때, 사물 인터넷이 연결된 임의의 차의 인덱스를 `idx` 라고 한다면, 
해당 차가 연료를 사용하여도 도달하지 못하는 인덱스가 나타났을 때 탐색을 종료하면 된다.

3. 차는 일렬로 배치되었다는 점에 근거하여, 
차가 다음방향 `->` 으로 이동하는 경우와 
이전방향 `<-` 으로 이동하는 경우를 탐색하자.

 */

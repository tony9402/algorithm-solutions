// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/a548c2ea425541dd82f89145600468f1

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

            List<Integer> list[] = new ArrayList[N + 1];
            for (int i = 1; i <= N; i++) {
                list[i] = new ArrayList<>();
            }

            for (int i = 0; i < M; i++) {
                int n1 = rd.nextInt();
                int n2 = rd.nextInt();

                list[n1].add(n2);
                list[n2].add(n1);
            }


            int[] g = new int[N + 1];
            boolean check = true;

            for (int i = 1; i <= N; i++) {
                if (g[i] == 0) {
                    check = bfs(i, g, list);
                }
                if (!check) break;
            }

            if (!check) sb.append("im");
            sb.append("possible").append("\n");
        }
        System.out.print(sb.toString());
    }

    private static boolean bfs(int st, int[] g, List<Integer> list[]) {
        Queue<Integer> q = new LinkedList<>();
        g[st] = 1;
        q.add(st);

        while (!q.isEmpty()) {
            int curr = q.poll();

            for (int next : list[curr]) {
                if (g[next] == g[curr]) return false;

                if (g[next] == 0) {
                    g[next] = g[curr] * -1;
                    q.add(next);
                }
            }
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

1. 그래프 응용 문제. 주어진 입력값을 통해 그래프를 형성하여 탐색했을 때,
   인접 노드끼리 색이 다른지 확인하는 방식으로 문제를 풀 수 있다.

2. 해당 풀이의 경우 색의 상태값을 `0,1,-1` 로 정했다.
   `0` 은 색이 칠해지지 않은 경우, `1,-1` 은 각각 색을 칠한 경우이며 색이 서로 다르다고 가정했다.
   만약 임의의 노드의 색을 `c` 라고 한다면, 다음 이동해야할 노드의 색은 `c*-1` 이어야 한다.

3. 그래프 탐색 중, 현재 노드와 다음 노드의 색이 동일한 경우가 발생한다면 `impossible` 을,
   탐색이 끝날때 까지 발생하지 않는다면 `possible` 을 출력한다.

 */

// Authored by: beberiche
// Co-authored by:
// Link: http://boj.kr/7c016fb410f24cd3995d7c6b25b945f4

import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        FastReader rd = new FastReader();
        int N = rd.nextInt();
        int M = rd.nextInt();
        int[] outDegree = new int[N + 1]; // 진출차수
        int[] inDegree = new int[N + 1]; // 진입차수
        List<int[]> list[] = new ArrayList[N + 1];
        for (int i = 1; i <= N; i++) {
            list[i] = new ArrayList<>();
        }

        for (int i = 0; i < M; i++) {
            int n1 = rd.nextInt();
            int n2 = rd.nextInt();
            int cnt = rd.nextInt();

            list[n1].add(new int[]{n2, cnt}); // 방향 그래프
            outDegree[n1]++;
            inDegree[n2]++;
        }

        Queue<Integer> q = new LinkedList<>();

        int[] dp = new int[N + 1];
        q.add(N);
        dp[N] = 1;
        while (!q.isEmpty()) {
            int curr = q.poll();

            for (int[] next : list[curr]) {
                dp[next[0]] += dp[curr] * next[1];
                inDegree[next[0]]--;
                if (inDegree[next[0]] == 0) {
                    q.add(next[0]);
                }
            }
        }
        StringBuilder sb = new StringBuilder();
        for (int i = 1; i <= N; i++) {
            if (outDegree[i] == 0) {
                sb.append(i).append(" ").append(dp[i]).append("\n");
            }
        }
        System.out.print(sb.toString());
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

1. 위상 정렬 응용 문제. 주어진 입력값에 대해 기본 부품, 중간 부품을 구분 하는 방법을 알면 쉽게 풀 수 있다.

2. 완제품으로 부터, 필요한 부품들을 찾아 그래프를 형성하는 경우,
   기본 부품은 리프 노드에 해당하며, 더이상 탐색이 진행 되지 않는,
   즉 `outDegree`(진출차수) 가 `0` 인 노드를 의미한다.
   반대로 `outDegree` 가 `0` 보다 크다면, 해당 노드는 완제품 혹은 중간 부품에 해당한다.

3. 해당 문제의 경우, `N` 이 완제품이므로,
   `N` 을 제외한 `outDegree` 가 `0` 보다 큰 노드는 모두 중간 부품이 된다.

4. 입력 값 마다 `inDegree` 와 `outDegree` 를 구한 후,
   완제품 `N` 을 시작으로 위상 정렬 탐색을 진행한다.
   만약 부모 노드가 `n` 개 필요한 경우,
   필요한 부품은  $n*cnt_{idx}$ 의 총합이 된다. 이를 `dp` 점화식으로 표현하자면 다음과 같다.
   $dp[p] = dp[p] + (dp[c] * cnt)$

5. 누적된 `dp[]` 내에서, 기본 제품만 골라 해당 노드의 인덱스와 누적값을 출력하면 정답이 된다.

 */

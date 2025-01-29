// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/0c55f16c74d441e7ad5f3ca44acc87b9

import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        FastReader rd = new FastReader();

        HashMap<Integer, int[]> m = new HashMap<>();
        Queue<int[]> q = new LinkedList<>();
        int a[] = new int[]{0, 0, 0, 0, 0};
        m.put(0, a);
        q.add(a);

        while (!q.isEmpty()) {
            int[] curr = q.poll();
            int sum = curr[0] * 60 + curr[1] * 10 + curr[2] * -10 + curr[3] - curr[4];

            // MINO
            if (check(m, sum - 1)) {
                m.put(sum - 1, new int[]{curr[0], curr[1], curr[2], curr[3], curr[4] + 1});
                q.add(m.get(sum - 1));
            }

            // ADDO
            if (check(m, sum + 1)) {
                m.put(sum + 1, new int[]{curr[0], curr[1], curr[2], curr[3] + 1, curr[4]});
                q.add(m.get(sum + 1));
            }

            // MINT
            if (check(m, sum - 10)) {
                m.put(sum - 10, new int[]{curr[0], curr[1], curr[2] + 1, curr[3], curr[4]});
                q.add(m.get(sum - 10));
            }

            // ADDT
            if (check(m, sum + 10)) {
                m.put(sum + 10, new int[]{curr[0], curr[1] + 1, curr[2], curr[3], curr[4]});
                q.add(m.get(sum + 10));
            }

            // ADDH
            if (check(m, sum + 60)) {
                m.put(sum + 60, new int[]{curr[0] + 1, curr[1], curr[2], curr[3], curr[4]});
                q.add(m.get(sum + 60));
            }
        }

        int T = rd.nextInt();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < T; i++) {
            int time = rd.nextInt();
            int ans[] = new int[]{0, 0, 0, 0, 0};
            int ret = time / 60;
            ans[0] = ret;
            int[] rem = m.get(time % 60);
            for (int j = 0; j < 5; j++) {
                ans[j] += rem[j];
                sb.append(ans[j]).append(" ");
            }
            sb.append("\n");
        }
        System.out.print(sb.toString());
    }

    private static boolean check(HashMap<Integer, int[]> m, int next) {
        return next >= 0 && next <= 60 && !m.containsKey(next);
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

1. BFS 응용 문제. 단순히 BFS로만 해결하려는 경우,
   `N` 의 최대 크기가 `1e7` 이기에 시간초과가 나오기 때문에, 다른 접근법을 신경써야 한다.

2. 주어진 시간의 변화를 주는 최대 크기는 `60` 이다. 즉 `0~59` 이하의 버튼의 최소 횟수를 미리 구하여,
   테스트 케이스 `N` 에 대하여 `N/60`  과 `N%60` 을 결합하는 방법으로 `N` 에 대한 버튼의 최소 횟수를 구할 수 있다.

3. 버튼에는 시간을 감소시키는 경우가 존재한다.
   가령 `48` 의 경우, `ADDH` 를 적용시킨 `1 0 1 0 2`  버튼의 최소 횟수가 된다.
   따라서 실제 구해야하는 시간의 변화는 `0~59` 이지만, `ADDH` 를 적용시킨 경우를 포함하기 위해
   다음 노드로 향하는 `BFS` 의 탐색 조건은 `0<=t<=60` 이 되어야 한다.

 */

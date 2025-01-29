// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/2e29afb6d303472aaea0da80d1ff77b4

import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        FastReader rd = new FastReader();
        int N = rd.nextInt();
        int M = rd.nextInt();

        String a[] = new String[N];

        for (int i = 0; i < N; i++) {
            a[i] = rd.next();
        }

        int K = rd.nextInt();

        boolean visited[] = new boolean[N];
        int ans = 0;
        for (int i = 0; i < N; i++) {
            if (visited[i]) continue;

            visited[i] = true;
            int cnt = 0;
            for (int j = 0; j < M; j++) {
                if (a[i].charAt(j) == '0') cnt++;
            }

            if (cnt <= K && cnt % 2 == K % 2) {
                int max = 0;
                for (int j = 0; j < N; j++) {
                    if (a[i].equals(a[j])) {
                        visited[j] = true;
                        max++;
                    }
                }
                ans = Math.max(max, ans);
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

1. 브루트포스 문제. 주어진 `K` 를 통해, 임의의 열의 모든 불을 킬 수 있는지 없는지를 확인하고,
   만약 가능하다면 현재 행과 동일한 램프의 갯수를 세어, 최대의 경우의 수를 반환하는 것이다.

2. `K` 를 통해 모든 불을 킬 수 있는지 확인하는 경우는 다음과 같다.

    a. 임의의 열의 `0` 의 갯수는 `K` 의 수보다 작아야한다.
       이는 `K` 보다 `0` 이 많은 경우 램프를 모두 키지 못하기 때문이다.

    b. 임의의 열의 `0` 의 갯수가 짝수라면 `K` 도 짝수, 홀수라면 `K` 도 홀수여야한다.
       스위치는 무조건 `K` 번 입력된다. 따라서 동일한 버튼을 2번 눌러 램프를 기존 상태로 변경하는 것이 가능하다.
       즉, 6번을 눌러야 한다면 8번, 10번을 누르더라도 동일하게 만들 수 있는 것이다.
       단, 홀수라면 어떻게 누르더라도 `K` 에 도달하기까지 1 이 남으므로,
       짝수-홀수/홀수-짝수 의 경우는 동일한 상태가 되지 못하는 것이다.

 */

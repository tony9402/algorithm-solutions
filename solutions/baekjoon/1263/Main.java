// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/81bc2dd6260e4d389b17384e1faa875a

import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        FastReader rd = new FastReader();
        int N = rd.nextInt();
        int[][] a = new int[N][2];

        for (int i = 0; i < N; i++) {
            a[i][0] = rd.nextInt();
            a[i][1] = rd.nextInt();
        }

        Arrays.sort(a, (n1, n2) -> n2[1] - n1[1]);


        int ans = a[0][1] - a[0][0];
        for (int i = 1; i < N; i++) {
            if (a[i][1] < ans) ans = a[i][1];
            ans -= a[i][0];
        }

        System.out.println((ans < 0) ? -1 : ans);
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

1. 그리디 문제. 
   결과적으로 일을 시작하는 시간을 최대한 늦게 시작하기 위해서는,
   주어진 일들을 가능한 빨리 끝내야한다는 것을 의미한다. 
   즉, 이전의 일이 끝나자마자 바로 다음 일을 시작하는 것이다.

2. 따라서, 이전의 일이 끝난 시간은 `t` 라고 했을 때, 
   `t` + `Ti` ≤ `Si` 가 모두 성립하는지 확인하면 된다.

3. 끝나는 시간을 기준으로 정렬하여, 임의의 시작점을 기준으로 위의 조건이 성사되는지 탐색을 진행한다.
    a. 내림차순으로 정렬하여, 입력값을 탐색마다 차감하는 방식으로 정답을 구하거나
    b. 오름차순으로 정렬하여, 매개변수 탐색을 통해 정답을 구하는 것도 가능하다.

 */


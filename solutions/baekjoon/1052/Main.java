// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/d003597712fb4a0e9bf95928abb647c5

import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        FastReader rd = new FastReader();

        int N = rd.nextInt();
        int K = rd.nextInt();

        for (int i = N; i <= Integer.MAX_VALUE; i++) {
//            Integer.bitCount를 직접 구현하는 경우
//            int bit = 0;
//            int cnt = 0;
//            while (i >= (1 << bit)) {
//                if ((i & 1 << bit) != 0) {
//                    cnt++;
//                }
//                bit++;
//            }
//
//            if (cnt <= K) {
//                System.out.println(i - N);
//                return;
//            }

            if (Integer.bitCount(i) <= K) {
                System.out.println(i - N);
                return;
            }
        }
        System.out.println(-1);
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

1. 이진법 문제. 입력값 `N` 에 대한 물병의 갯수는 $2^N$ 으로 표현할 수 있는 최소한의 갯수가 된다.

2. 예를 들어 13의 경우를 $2^N$ 으로 표현한다면 다음과 같다.

    ```
    2^0 * 13 // 13개
    2^1 * 6 + 2^0 * 1 // 7개
    2^2 * 3 + 2^0 * 1 // 4개
    2^3 * 1 + 2^2 * 1 + 2^0 + 1 // 3개, 1101
    ```

    즉, 현재 13이 차지하는 물병은 3개가 되는 것이며, 여기에 `2^0 = 1` 의 물을 추가하여 물병의 수를 줄일 수 있다.

3. 요약하자면 비트마스킹을 활용하여 `N` 을 시작으로,
   비트가 `1` 이 되는 갯수가 `K` 이하가 되는 경우를 찾으면 되는 것이다.

4. `&` 연산을 활용하여도 정답을 받을 수 있으나,
	자바의 경우 `Integer.bitCount()` 라는 편리한 메서드가 있으니 이를 활용하자. (시간도 대폭 빨라진다.)

 */

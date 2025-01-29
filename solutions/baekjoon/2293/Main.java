// Authored by: 336699go
// Co-authored by: -
// Link: http://boj.kr/06a33314bada4e6cbb75b91eb3b4f498

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        FastReader br = new FastReader();
        int n = br.nextInt();
        int k = br.nextInt();
        int[] coins = new int[n];
        int[] dp = new int[k + 1];

        for (int i = 0; i < n; i++) {
            coins[i] = br.nextInt();
        }

        dp[0] = 1;

        for (int i = 0; i < n; i++) {
            for (int j = coins[i]; j <= k; j++) {
                dp[j] = dp[j] + dp[j - coins[i]];
            }
        }

        System.out.println(dp[k]);
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
배낭 문제와 유사하나 1+2, 2+1 같은 중복을 신경 써야 한다.  
점화식: dp[j] = dp[j] + dp[j - coins[i]] = i번째 동전까지만 사용해서 가치의 합이 j원이 되는 경우의 수  
메모리 제한이 빡빡해서 dp 배열을 2차원이 아닌 1차원 배열로 해야 한다. 
*/

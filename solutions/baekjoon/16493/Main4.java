// Authored by : tony9402
// Co-authored by : -
// Link : http://boj.kr/33e7953989844e5ead8d5e123c9df8ea
import java.io.*;
import java.util.*;
import java.lang.*;

public class Main {
    static public void main(String[] args) {
        FastReader rd = new FastReader();

        int N = rd.nextInt(), M = rd.nextInt();
        int [][]DP = new int[N + 1][M + 1];

        int ans = 0;
        for(int k = 1; k <= M; ++k) {
            int day = rd.nextInt();
            int page = rd.nextInt();
            for(int i = day; i <= N; ++i) {
                int mx = 0;
                for(int j = 1; j < k; ++j) {
                    mx = Math.max(mx, DP[i - day][j]);
                }
                DP[i][k] = mx + page;
                ans = Math.max(ans, DP[i][k]);
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
            while(st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                }
                catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() { return Integer.parseInt(next()); }
        long nextLong() { return Long.parseLong(next()); }
        double nextDouble() { return Double.parseDouble(next()); }
        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            }
            catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }
}

/* Solution Description 

DP[i][j]: i일에 j번 챕터를 다 읽었을 때 최대 페이지 수

```DP[i][j] = max(DP[i - days[j]][1..j-1]) + pages[j]```

시간복잡도: O(NM^2)  

## Quiz!  
여기서 디피 테이블을 일차원으로 바꿀수가 있습니다. 어떻게 할 수 있을까요?  
*/
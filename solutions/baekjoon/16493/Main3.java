// Authored by : tony9402
// Co-authored by : -
// Link : http://boj.kr/79b5da13184148b1bfc38da7a6f8a67c
import java.io.*;
import java.util.*;
import java.lang.*;

public class Main {
    static public void main(String[] args) {
        FastReader rd = new FastReader();

        int N = rd.nextInt(), M = rd.nextInt();
        int []days = new int[M + 1];
        int []pages = new int[M + 1];
        for(int i = 1; i <= M; ++i) {
            days[i] = rd.nextInt();
            pages[i] = rd.nextInt();
        }

        int []DP = new int[6001];
        for(int i = 1; i <= 6000; ++i) {
            DP[i] = Integer.MAX_VALUE;
        }
        for(int k = 1; k <= M; ++k) {
            for(int i = 6000; i >= pages[k]; --i) {
                if(DP[i - pages[k]] == Integer.MAX_VALUE) continue;
                DP[i] = Math.min(DP[i], DP[i - pages[k]] + days[k]);
            }
        }
        int ans = 0;
        for(int i = 1; i <= 6000; ++i) {
            if(DP[i] <= N) {
                ans = i;
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

DP[i]: i 페이지를 읽는데 걸린 최소 일 수
```DP[i] = min(DP[i - pages[k]] + days[k])```

i를 뒤에서부터 채워야 아이템을 한번씩 채울 수 있다.  
앞에서부터 채운다면 챕터를 i일 동안 2번 이상 읽은걸로 채워지기 때문이다.  

```cpp
for k 1...M
    for i N...1
        DP[i] = max(DP[i - pages[k]] + days[k])
```

시간복잡도: O(6000M)
*/
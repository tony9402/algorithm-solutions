// Authored by : tony9402
// Co-authored by : -
// Link : http://boj.kr/9bd0c1ea65e540acb37909f93914917a
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

        int []DP = new int[N + 1];
        int ans = 0;
        for(int k = 1; k <= M; ++k) {
            for(int i = N; i >= days[k]; --i) {
                DP[i] = Math.max(DP[i], DP[i - days[k]] + pages[k]);
                ans = Math.max(ans, DP[i]);
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

DP[i]: i일 동안 j개의 챕터를 읽었을 때 읽은 최대 페이지 수  
```DP[i] = max(DP[i - days[k]] + pages[k])```
i를 뒤에서부터 채워야 아이템을 한번씩 채울 수 있다.  
앞에서부터 채운다면 챕터를 i일 동안 2번 이상 읽은걸로 채워지기 때문이다.  

```cpp
for k 1...M
    for i N...1
        DP[i] = max(DP[i - days[k]] + pages[k])
```

시간복잡도: O(NM)

Quiz!
또 다른 디피 점화식으로 문제를 풀 수 있습니다 !  
어떻게 점화식을 세울 수 있을까요?  
*/
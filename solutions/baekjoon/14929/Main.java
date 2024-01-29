// Authored by : rhljh201
// Co-authored by : tony9402
// Link : http://boj.kr/f527fd10e06b494e914855455f19a96a
import java.util.*;
import java.lang.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        FastReader rd = new FastReader();
        int N = rd.nextInt();

        int[] O = new int[N + 1];
        int[] A = new int[N + 1];

        for(int i=1; i<=N; i++){
            O[i] = rd.nextInt();
            A[i] = A[i-1] + O[i];
        }

        long sum = 0;
        for(int i=1; i<=N; i++){
            sum += A[i-1]*O[i];
        }

        System.out.println(sum);
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
N = 3이라면, (1)*2 + (1 + 2) * 3
N = 4라면, (1)*2 + (1 + 2)*3 + (1 + 2 + 3)*4
이런식으로 식을 정리할 수 있다. 따라서 구간합을 구한 다음 구간합 배열[i-1] * 값[i]를 해주면 계산할 수 있다.
*/

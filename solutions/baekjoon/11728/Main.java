// Authored by : rhljh201
// Co-authored by : tony9402
// Link : http://boj.kr/4fdd45f2774645908eac3abcabfe01d3
import java.io.*;
import java.util.*;
import java.lang.*;

public class Main {
    public static void main(String[] args) throws IOException {
        FastReader rd = new FastReader();

        int N = rd.nextInt();
        int M = rd.nextInt();

        int[] A = new int[N];
        int[] B = new int[M];

        for(int i=0; i<N; i++){
            A[i] = rd.nextInt();
        }

        for(int i = 0; i<M; i++){
            B[i] = rd.nextInt();
        }

        int x = 0;
        int y = 0;
        StringBuilder sb = new StringBuilder();
        // 정렬
        for(int i=0; i<M+N; i++){
            if(x == N) sb.append(B[y++]).append(" ");
            else if(y == M) sb.append(A[x++]).append(" ");
            else {
                if (A[x] > B[y]) sb.append(B[y++]).append(" ");
                else if (A[x] <= B[y]) sb.append(A[x++]).append(" ");
            }
        }
        System.out.println(sb);
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
정렬된 두 배열을 입력받은 후 투 포인터를 비교하면서 작은 값부터 새로운 배열에 넣어주면 하나의 정렬된 배열로 합칠 수 있다.
*/

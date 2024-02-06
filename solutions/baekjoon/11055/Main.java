// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/56d89f380aca45a0b68271d3b1e4a17e
import java.util.*;
import java.io.*;
import java.lang.*;

public class Main{
	public static void main(String[] args){
        FastReader rd = new FastReader();

        int N = rd.nextInt();
        int[] DP = new int[N + 1];
        int[] arr = new int[N + 1];

        for(int i = 1; i <= N; ++i) {
            arr[i] = rd.nextInt();
        }

        int ans = 0;
        for(int i = 1; i <= N; ++i) {
            for(int j = 1; j < i; ++j) {
                if(arr[j] < arr[i]) {
                    DP[i] = Math.max(DP[i], DP[j]);
                }
            }
            DP[i] += arr[i];
            ans = Math.max(ans, DP[i]);
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
DP[i]: i 번째 수가 증가하는 부분 수열의 맨 마지막일 때 부분 수열의 합 중 최대
DP[i]: max_{1≤j<i, arr[j]<arr[i]}(DP[j]) + arr[i]

답: max_{1≤i≤N}(DP[i])
*/
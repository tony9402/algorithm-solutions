// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/ace0332bace54c889a82468252cd8e63
import java.util.*;
import java.io.*;
import java.lang.*;

public class Main{
	public static void main(String[] args){
        FastReader rd = new FastReader();

        int Q = rd.nextInt();
        long minValue = -1_000_000_000_000_000_000L;
        long maxValue =  1_000_000_000_000_000_000L;

        int ans = Q + 1;
        for(int q = 1; q <= Q; ++q) {
            long x = rd.nextLong();
            String v = rd.next();

            if(v.equals("^")) {
                minValue = Math.max(minValue, x + 1);
            }
            else {
                maxValue = Math.min(maxValue, x - 1);
            }

            if(minValue > maxValue) {
                System.out.println("Paradox!");
                System.out.print(q);
                return;
            }
            else if(minValue == maxValue) ans = Math.min(ans, q);
        }

        if(minValue == maxValue) {
            System.out.println("I got it!");
            System.out.print(ans);
        }
        else {
            System.out.println("Hmm...");
        }
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
[minValue, maxValue] 구간을 잡고 주어지는 값을 보고 범위를 줄여나가면서 답은 찾아나가면 되는 문제.
쿼리 중간에 minValue > maxValue가 되는 순간이 있다 -> Paradox!
minValue == maxValue => 답을 찾을 수 있음 (I got it!)
*/
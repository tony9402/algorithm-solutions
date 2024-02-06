// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/6e26bd76ac6b44429522a972da812cf7
import java.util.*;
import java.io.*;
import java.lang.*;

public class Main{
    static String DKSH = "DKSH";
	public static void main(String[] args){
        FastReader rd = new FastReader();

        int N = rd.nextInt();
        String S = rd.next();
        long[] DP = new long[5];

        DP[0] = 1;
        for(int i = 1; i <= N; ++i) {
            int idx = get_index(S.charAt(i - 1));
            if(idx > 0) {
                DP[idx] += DP[idx - 1];
            }
        }

        System.out.print(DP[4]);
	}

    static public int get_index(char ch) {
        for(int i = 0; i < 4; ++i) {
            if(DKSH.charAt(i) == ch) return i + 1;
        }
        return 0;
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
1번 서브태스크:
완전탐색 O(N^4)  
솔루션 코드: http://boj.kr/20dae18c53344637804b3a27d070bce9  

2번 서브태스크:  
O(N^2)  
DP[i][j]: i번째 알파벳이 "DKSH" 중 j번째 알파벳까지 만드는 경우의 수  
DP[0][0] = 1 => ""를 만드는 경우의 수 (기저 값)  
DP[i][j]: ∑ DP_{0≤k<i}[k][j-1] (i번째 알파벳이 "DKSH" 중에 하나인 경우에만)  
솔루션 코드: http://boj.kr/efe73e4d06434af09f81e443108179b2  

3번 서브태스크:
O(N)  
DP[0] = 1 => ""를 만드는 경우의 수 (기저 값)  
DP[i]: "DKSH" 중 i번째 알파벳까지 만드는 경우의 수  
현재 값이 "DKSH" 중에 하나이고 i번째 값이라 하면 DP[i] += D[i - 1]  
솔루션 코드: http://boj.kr/6e26bd76ac6b44429522a972da812cf7  
*/
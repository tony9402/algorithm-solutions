// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/c68fb2fa6cb548ba8481da5bb9212086
import java.util.*;
import java.io.*;
import java.lang.*;

public class Main{
	public static void main(String[] args){
        FastReader rd = new FastReader();

        int T = rd.nextInt();
        while(T --> 0) {
            int N = rd.nextInt(), M = rd.nextInt();
            char map[][] = new char[N][M];

            int answer = 0;
            for(int i = 0; i < N; ++i) {
                String line = rd.next();

                for(int j = 0; j < M; ++j) {
                    map[i][j] = line.charAt(j);
                }
            }

            for(int i = 0; i < N; ++i) {
                for(int j = 0; j + 2 < M; ++j) {
                    if(map[i][j] == '>' && map[i][j + 1] == 'o' && map[i][j + 2] == '<') {
                        ++ answer;
                    }
                }
            }

            for(int j = 0; j < M; ++j) {
                for(int i = 0; i + 2 < N; ++i) {
                    if(map[i][j] == 'v' && map[i + 1][j] == 'o' && map[i + 2][j] == '^') {
                        ++ answer;
                    }
                }
            }

            // 출력이 많은 경우 StringBuilder로 출력해야 빠름
            System.out.println(answer);
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
이차원 배열을 돌면서 사탕 두 가지가 존재하는지 잘 세면 되는 문제.
탐색 중 인덱스를 넘어가는 것을 주의해야한다.
*/
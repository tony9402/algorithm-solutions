// Authored by: tony9402
// Co-authored by: -
// Link: http://boj.kr/7ee1380921d24e86bda292ad9d8ba630
import java.util.*;
import java.io.*;
import java.lang.*;

public class Main{
	public static void main(String[] args){
        FastReader rd = new FastReader();

        int N = rd.nextInt(), M = rd.nextInt();
        int S = rd.nextInt(), E = rd.nextInt();

        List<Integer> G[] = new ArrayList[N + 1];
        int used[] = new int[N + 1];
        
        for(int i = 1; i <= N; ++i) {
            G[i] = new ArrayList<>();
            used[i] = -1;
        }

        for(int i = 0; i < M; ++i) {
            int u = rd.nextInt(), v = rd.nextInt();
            G[u].add(v);
            G[v].add(u);
        }

        Queue<Integer> Q = new LinkedList<>();
        Q.add(S);
        used[S] = 0;

        while(!Q.isEmpty()) {
            int cur = Q.poll();

            for(int nxt: G[cur]) {
                if(used[nxt] == -1) {
                    used[nxt] = used[cur] + 1;
                    Q.add(nxt);
                }
            }
            if(cur > 1 && used[cur - 1] == -1) {
                used[cur - 1] = used[cur] + 1;
                Q.add(cur - 1);
            }
            if(cur < N && used[cur + 1] == -1) {
                used[cur + 1] = used[cur] + 1;
                Q.add(cur + 1);
            }
        }

        System.out.println(used[E]);
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
갈 수 있는 곳들을 그래프로 변환 후 S에서 E로 가는 최단거리를 구하면 되는 문제
*/
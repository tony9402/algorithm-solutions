// Authored by : qudfbf2
// Co-authored by : -
// Link : http://boj.kr/04fdd08a57f843d787e56b81bd60d798

import java.util.*;
import java.io.*;

public class Bj_1822 {
    public static void main(String[] args) {
        FastReader rd = new FastReader();
        StringBuilder sb = new StringBuilder();

        int nA = rd.nextInt();
        int nB = rd.nextInt();

        HashSet<Integer> set = new HashSet<>();
        // 집합 A에는 속하면서 집합 B에는 속하지 않는 원소 (이하 A-B 로 표현) 의 개수를 구하기 위해
        while (nA-- > 0) {
            set.add(rd.nextInt()); // set에 먼저 집합 A의 원소를 추가
        }
        while (nB-- > 0) {
            set.remove(rd.nextInt()); // 집합 A와 중복되는 집합 B의 원소를 제거
        }

        // A-B 원소의 개수 출력
        sb.append(set.size()).append("\n");
        // A-B 원소가 있다면 증가하는 순서로 출력
        if (!set.isEmpty()) {
            ArrayList<Integer> list = new ArrayList<>(set); // 정렬하기 위해 Set to List 변환
            Collections.sort(list); // 오름차순 정렬
            for (int it : list) {
                sb.append(it).append(" ");
            }
        }
        System.out.print(sb);
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
집합 A에서 집합 B와 겹치는 원소만 제거하면 되는 문제
먼저 A-B 차집합을 구하고 정렬해서 출력하는 방식으로 해결 (HashSet + sort)
HashSet + sort 대신 TreeSet을 사용해서 해결할 수도 있다
*/
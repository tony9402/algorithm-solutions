// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/92ba32984b594dd68c8353a90fb75743

import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        FastReader rd = new FastReader();
        int N = rd.nextInt();
        int K = rd.nextInt();

        int[] a = new int[N + 1];
        for (int i = 1; i <= N; i++) {
            int num = 1;
            String str = rd.next();
            int total = 0;
            for (int j = K - 1; j >= 0; j--) { // 이진코드 -> int화
                int val = str.charAt(j) - '0';
                if (val == 1) {
                    total += val * num;
                }
                num *= 2;
            }
            a[i] = total;
        }

        int A = rd.nextInt();
        int B = rd.nextInt();
        Queue<Node> q = new LinkedList<>();
        q.add(new Node(a[A], A+""));
        boolean visited[] = new boolean[N + 1];
        visited[A] = true;

        String ans = "-1";
        while (!q.isEmpty()) {
            Node curr = q.poll();
            if (curr.num == a[B]) {
                ans = curr.path;
                break;
            }

            for (int i = 1; i <= N; i++) {
                if (visited[i] || a[i] == curr.num) continue;

                if (Integer.bitCount(curr.num ^ a[i]) == 1) {
                    visited[i] = true;
                    q.add(new Node(a[i], curr.path + " " + i));
                }
            }
        }

        System.out.println(ans);
    }

    private static class Node {
        int num;
        String path;

        Node(int num, String path) {
            this.num = num;
            this.path = path;
        }
    }

    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }

        String nextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }
    }
}

/* Solution Description

1. 비트마스킹 응용 문제로, 해밍비트가 1인 경우를 코드로 구현할 수 있다면 쉽게 문제를 해결할 수 있다.

2. 더불어, `A->B` 까지의 가장 짧은 해밍 비트 경로를 찾아야하므로, `BFS` 를 적용했다.

3. 임의의 코드에 대해, 동일한 코드가 아니며 아직 방문하지 않은 코드 가운데,
   두 코드를 `XOR` 연산을 했을 때, 참인 비트의 수가 `1` 인 경우에 대해 탐색을 이어가는 방식으로 문제를 해결할 수 있다.

 */

// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/d1c4ba48c0c0449d97bb1a5aa5087902

import java.util.*;
import java.io.*;

public class Main {
    private static long s, t;

    public static void main(String[] args) {
        FastReader rd = new FastReader();

        s = rd.nextLong();
        t = rd.nextLong();

        if (s == t) {
            System.out.println(0);
            return;
        }

        Queue<Node> q = new LinkedList<>();
        HashSet<Long> h_set = new HashSet<>();
        q.add(new Node(s * s, "*"));
        h_set.add(s * s);
        q.add(new Node(s + s, "+"));
        h_set.add(s + s);
        q.add(new Node(1L, "/"));
        h_set.add(1L);


        boolean check = false;
        while (!q.isEmpty()) {
            Node curr = q.poll();
            if (curr.num == t) {
                System.out.println(curr.str);
                check = true;
                q.clear();
                break;
            }

            if (curr.num > 1e9) continue;

            long num = curr.num;
            if (!h_set.contains(num * num)) {
                h_set.add(num * num);
                q.add(new Node(num * num, curr.str + "*"));
            }

            if (!h_set.contains(num + num)) {
                h_set.add(num + num);
                q.add(new Node(num + num, curr.str + "+"));
            }


        }

        if (!check) System.out.println(-1);
    }


    static class Node {
        long num;
        String str;

        Node(long num, String str) {
            this.num = num;
            this.str = str;
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

1. BFS 응용문제. 문제에 대한 이해도가 어느정도 필요한 문제이다.

2. 단순히 4연산을 모두 반영하여 문제를 해결하는 방법도 있으나, 
   사실 2연산 탐색을 추구하여도 충분히 문제를 풀 수 있는 문제이다.  
   `-` , `/` 의 경우 어떤 `s`값이라 할지라도 `0` , `1` 이 반환된다. 
   즉, 임의의 탐색을 진행하는 도중에 `-`, `/` 를 사용하는 것보다
   맨 처음연산에 `-` , `/` 을 반영하는 경우가 더욱 연산횟수가 적을 수 밖에 없다.
   
3. 더불어, `s,t` 의 입력값의 범위는 `1 <= s,t <= 1e9` 이므로 
   사실상 `-` 연산은 출력값에 절대 반영될 수 없다.

4. 따라서, 이 문제는 첫 연산에서만 `*,+,/` 연산을 반영하고, 
   나머지 탐색 연산에서는 `*,+` 만 사용하는 것으로도 정답을 도출할 수 있다.

5. 이외에 해당 문제에서 조심해야할 부분들을 다음과 같다. 
    
    a. 재방문 처리를 진행하기 위해서 배열을 사용할 수 없다. 입력 범위가 너무 크기 때문이다. 
       `Set` 이나 `Map` 을 활용하여 해결하자.
    b. `*,+` 연산 시 `int` 범위를 넘어갈 수 있다.

 */

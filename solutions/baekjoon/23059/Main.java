// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/4dbb97429a544705b8b5a4fd422048eb

import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        FastReader rd = new FastReader();
        int N = rd.nextInt();
        // 아이템 -> idx
        TreeMap<String, Integer> m = new TreeMap<>();
        // 아이템 -> 아이템
        TreeMap<String, List<String>> mm = new TreeMap<>();
        int[] inDegree = new int[N * 2 + 4];
        int idx = 0;
        for (int i = 0; i < N; i++) {
            String i1 = rd.next();
            String i2 = rd.next();

            if (!m.containsKey(i1)) m.put(i1, idx++);
            if (!m.containsKey(i2)) m.put(i2, idx++);

            if (!mm.containsKey(i1)) mm.put(i1, new ArrayList<>());
            if (!mm.containsKey(i2)) mm.put(i2, new ArrayList<>());

            inDegree[m.get(i2)]++;
            mm.get(i1).add(i2);
        }

        Queue<Node> q = new LinkedList<>();

        for (String item : m.keySet()) {
            if (inDegree[m.get(item)] == 0) {
                q.add(new Node(item, 0));
            }
        }

        PriorityQueue<Node> pq = new PriorityQueue<>((n1, n2) -> {
            if (n1.degree == n2.degree) return n1.item.compareTo(n2.item);
            return n1.degree - n2.degree;
        });

        while (!q.isEmpty()) {
            Node curr = q.poll();
            pq.add(curr);

            for (String next : mm.get(curr.item)) {
                int nextIdx = m.get(next);
                inDegree[nextIdx]--;
                if (inDegree[nextIdx] == 0) {
                    q.add(new Node(next, curr.degree + 1));
                }
            }
        }


        if (idx != pq.size()) {
            System.out.println(-1);
            return;
        }

        StringBuilder sb = new StringBuilder();
        while (!pq.isEmpty()) {
            sb.append(pq.poll().item).append("\n");
        }

        System.out.print(sb.toString());
    }

    static class Node {
        String item;
        int degree;

        Node(String item, int degree) {
            this.item = item;
            this.degree = degree;
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

1. 위상정렬 응용 문제. 위상정렬을 통해 모든 탐색이 가능한지를 확인하여,
   위상정렬 단계 및 아이템 사전 순으로 정렬된 상태로 출력을 해야한다.

2. 초기 `q` 에 삽입되는 위상정렬 단계는 `0` 으로 설정하며,
   현재 노드에서 다음으로 이동할 노드가 존재하는 경우 (진입 차수가 `0` 인 노드)
   `현재 노드의 위상정렬 단계 + 1` 의 값을 다음 이동 노드에 반영한다.

3. 우선순위 큐를 생성하여, 반환되는 큐의 노드 순으로 우선순위 큐에 담아준다.
   위상정렬 탐색 완료 이후, 만약 아이템의 갯수와 우선순위 큐의 사이즈가 동일하다면,
   모든 아이템을 구할 수 있는 경우이며 우선순위 큐의 노드들을 순서대로 출력하자.

4. 아이템의 갯수와 우선순위 큐의 사이즈가 동일하지 못하다면,
   현재 주어진 선후 관계로는 모든 아이템을 구매하지 못하는 경우이다.
   (-1을 출력하자.)

 */

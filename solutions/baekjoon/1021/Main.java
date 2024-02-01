//Authored by : lms0806
//Co-authored by : -
//Link : http://boj.kr/3e77da6b94d94b15863c1f94f231fa17

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Deque;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        LinkedList<Integer> deque = new LinkedList<>();

        int n = Integer.parseInt(st.nextToken()) + 1, m = Integer.parseInt(st.nextToken());
        while(n --> 1) {
            deque.offerFirst(n);
        }

        int answer = 0;
        st = new StringTokenizer(br.readLine());
        while(m --> 0) {
            int num = Integer.parseInt(st.nextToken());

            int targetidx = deque.indexOf(num);
            int halfidx = deque.size() % 2 == 0 ? deque.size() / 2 - 1 : deque.size() / 2;

            if(targetidx <= halfidx) {
                while(targetidx --> 0) {
                    deque.offerLast(deque.poll());
                    answer++;
                }
            }
            else {
                int size = deque.size() - targetidx;
                while(size --> 0) {
                    deque.offerFirst(deque.pollLast());
                    answer++;
                }
            }
            deque.poll();
        }
        System.out.print(answer);
    }
}
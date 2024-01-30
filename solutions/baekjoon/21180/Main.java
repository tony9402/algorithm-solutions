//Authored by : qudfbf2
//Co-authored by : -
//Link : boj.kr/835735b341ba46abb792c749652b34f9

import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        FastReader rd = new FastReader();

        int n = rd.nextInt();
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = rd.nextInt(); // 주어지는 정수들을 배열에 저장한다
        }
        for (int i = 0; i < n; i++) {
            int x = arr[i]; // 숫자 하나를 정한다
            int sum = 0;
            for (int j = 0; j < n; j++) {
                if (i == j) continue; // 자기자신을 제외하고
                sum += arr[j]; // 나머지 정수들을 더하여 합을 구한다
            }
            if (x == sum) { // 나머지 정수들의 합과 x가 같다면
                System.out.print(x); // x를 출력하고 프로그램을 종료한다
                return;
            }
        }
        // 모든 정수들에 대해 만족한 값이 없으면 "BAD"를 출력한다
        System.out.print("BAD");
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
n개의 정수를 자기자신을 제외한 나머지 정수의 합이 자신과 같은지 확인하는 문제
 */

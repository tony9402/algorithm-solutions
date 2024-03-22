// Authored by: beberiche
// Co-authored by: -
// Link: http://boj.kr/ce87335721bb43a89f6a1ac8834917d9
import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) throws Exception {
        FastReader rd = new FastReader();

		int N = rd.nextInt();

		int[][] a = new int[N][4];
		for (int i = 0; i < N; i++) {
			a[i][0] = rd.nextInt();
			a[i][1] = rd.nextInt();
			a[i][2] = rd.nextInt();
			a[i][3] = rd.nextInt();
		}

        int[] ab = new int[N * N];
		int idx = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				ab[idx++] = a[i][0] + a[j][1];
			}
		}

		Arrays.sort(ab);
        long ans = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int cd = a[i][2] + a[j][3];
				ans += upperBound(ab, -cd) - lowerBound(ab, -cd);
			}
        }
		
         System.out.println(ans);

    }


    private static int lowerBound(int[] ab, int val) {
		int l = 0;
		int r = ab.length - 1;

		while (l <= r) {
			int mid = (l + r) / 2;

			if (ab[mid] >= val) {
				r = mid - 1;
			} else
				l = mid + 1;
		}
		return r;
	}

	private static int upperBound(int[] ab, int val) {
		int l = 0;
		int r = ab.length - 1;

		while (l <= r) {
			int mid = (l + r) / 2;

			if (ab[mid] > val) {
				r = mid - 1;
			} else
				l = mid + 1;
		}
		return r;
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

1. 중간에서 만니기의 기초 문제. 여러 알고리즘을 활용한 풀이가 가능하겠으나, 
   공통적으로 $O(N^4)$ 의 시간복잡도를 $O(2N^2)$ 으로 만드는 설계에 대한 이해가 필요하다.

2. `a,b,c,d` 가 가진 각각의 정수가 합이 `0` 이 나오는 경우는 
   `(a+b)+(c+d)` 역시 `0` 이 나올수 밖에 없다. 
    따라서 기존 4개의 항목을 `ab,cd` 라는 2개의 항목으로 줄여 시간초과 문제를 해결하자.

3. 본 풀이의 경우, 이분탐색을 활용했다. 
   `ab` 의 모든 경우의 합을 먼저 구한 후 이를 오름차순 정렬하여,
   `-cd` 의 값이 `ab` 의 요소에 존재하는지 확인하자.

4. 주어지는 정수의 최댓값은 $2^{28}$ 로, 4가지 정수의 덧셈으로는 `int` 를 넘지 않으나, 출력값은 `int` 를 넘을 수 있다. 
   모든 경우의 합이 `0` 이 나오는 입력이 있다고 가정한다면, 출력값은 최대 $4000^4 = 2.56e+14$ 가 되기 때문이다..

*/
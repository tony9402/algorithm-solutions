// Authored by : rhljh201
// Co-authored by : -
// Link : http://boj.kr/05eb6ff96ddc4cf79efada85efcfaf03

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt()+1;

        int[] O = new int[N];
        int[] A = new int[N];

        for(int i=1; i<N; i++){
            O[i] = sc.nextInt();
            A[i] = A[i-1] + O[i];
        }

        long sum = 0;
        for(int i=1; i<N; i++){
            sum += A[i-1]*O[i];
        }

        System.out.println(sum);
    }
}

/* Solution Description
N = 3이라면, (1)*2 + (1 + 2) * 3
N = 4라면, (1)*2 + (1 + 2)*3 + (1 + 2 + 3)*4
이런식으로 식을 정리할 수 있다. 따라서 구간합을 구한 다음 구간합 배열[i-1] * 값[i]를 해주면 계산할 수 있다.
*/
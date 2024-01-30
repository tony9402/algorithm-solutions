// Authored by: tony9402
// Co-authored by: lms0806
// Link: http://boj.kr/3b60c2a75fbc4c1cb0b1571046ceae36
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		System.out.print(Integer.parseInt(st.nextToken()) + Integer.parseInt(st.nextToken()));
	}
}

/* Solution Description
두 정수 A와 B를 입력받고 두 정수의 합의 결과를 출력하면 되는 문제
*/
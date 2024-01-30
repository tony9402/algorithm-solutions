// Authored by: lms0806
// Co-authored by: -
// Link: http://boj.kr/fbea125ef3714da4b712fdbd4415d43f
import java.util.*;
import java.io.*;
import java.lang.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());

		System.out.print(a - b);
	}
}

/* Solution Description
두 정수 A와 B를 입력받고 두 정수의 차의 결과를 출력하면 되는 문제
*/
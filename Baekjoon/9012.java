package Backjoon;

import java.io.IOException;
import java.util.Scanner;

import java.util.Stack;

public class 9012 {
	
	// 괄호 문자열(Parenthesis String, PS)은 두 개의 괄호 기호인 ‘(’ 와 ‘)’ 만으로 구성되어 있는 문자열이다.
	// 그 중에서 괄호의 모양이 바르게 구성된 문자열을 올바른 괄호 문자열(Valid PS, VPS)이라고 부른다.
	// 여러분은 입력으로 주어진 괄호 문자열이 VPS 인지 아닌지를 판단해서 그 결과를 YES 와 NO 로 나타내어야 한다. 
	public static String PScheck(String str) {
		
		Stack<Character> stack = new Stack<Character>();
		
		for(int strIdx = 0; strIdx < str.length(); strIdx++) {
			stack.push(str.charAt(strIdx));
			if(stack.size() >= 2) {
				if(stack.peek() == ')') {
					char right = stack.pop();
					if(stack.peek() == '(')
						stack.pop();
					else
						stack.push(right);
				}
			}
		}
		
		if(stack.isEmpty())
			return "YES";
		else
			return "NO";
	}

	public static void main(String[] args) throws IOException {
		
    	Scanner scanner = new Scanner(System.in);
    	// 입력은 T개의 테스트 데이터로 주어진다.
    	// 입력의 첫 번째 줄에는 입력 데이터의 수를 나타내는 정수 T가 주어진다. 
    	int T = scanner.nextInt();
    	
    	// 각 테스트 데이터의 첫째 줄에는 괄호 문자열이 한 줄에 주어진다. 하나의 괄호 문자열의 길이는 2 이상 50 이하이다.
    	for(int t = 0; t < T; t++) {
    		String inputString = scanner.next();
    		
    		// 만일 입력 괄호 문자열이 올바른 괄호 문자열(VPS)이면 “YES”, 아니면 “NO”를 한 줄에 하나씩 차례대로 출력해야 한다.
    		System.out.println(PScheck(inputString));
    	}
	
    	scanner.close();
	}

}

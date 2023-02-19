/**
 * 
 * 백준 1748번, 수 이어 쓰기 1
 * 190930
 * https://www.acmicpc.net/problem/1748
 * 
*/
#include <iostream>
using namespace std;

// 1부터 N까지의 수를 이어서 쓰면 다음과 같이 새로운 하나의 수를 얻을 수 있다.
int N;
// 1234567891011121314151617181920212223...
// 이렇게 만들어진 새로운 수는 몇 자리 수일까? 이 수의 자릿수를 구하는 프로그램을 작성하시오.
int ans = 0;

int main(){
    
    // 첫째 줄에 N(1≤N≤100,000,000)이 주어진다.
    cin >> N;

    for(int i = 1; i <= N; i++){
        int cur = i;
        int digit = 0;
        while(cur){
            cur /= 10;
            digit++;
        }
        ans += digit;
    }

    // 첫째 줄에 새로운 수의 자릿수를 출력한다.
    cout << ans << '\n';
    return 0;
}
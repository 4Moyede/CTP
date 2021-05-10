/**
 * 
 * Baekjoon 9095, 1, 2, 3 더하기
 * 210510
 * https://www.acmicpc.net/problem/9095
 * 
*/
#include <iostream>
#include <map>
using namespace std;

// 정수 n이 주어졌을 때, n을 1, 2, 3의 합으로 나타내는 방법의 수를 구하는 프로그램을 작성하시오.
// 합을 나타낼 때는 수를 1개 이상 사용해야 한다.
int T, n;

map<int, int> dp;

int main(){

    // 첫째 줄에 테스트 케이스의 개수 T가 주어진다. 
    cin >> T;

    dp[1] = 1; // n = 1 인 경우, (1)
    dp[2] = 2; // n = 2 인 경우, (2), (1, 1)
    dp[3] = 4; // n = 3 인 경우, (3), (1, 2), (2, 1), (1, 1, 1)

    for(int number = 4; number < 11; number++)
        dp[number] = dp[number - 3] + dp[number - 2] + dp[number - 1];

    // 각 테스트 케이스는 한 줄로 이루어져 있고, 정수 n이 주어진다. n은 양수이며 11보다 작다.
    for(int t = 0; t < T; t++){
        cin >> n;

        // 각 테스트 케이스마다, n을 1, 2, 3의 합으로 나타내는 방법의 수를 출력한다.
        cout << dp[n] << '\n';
    }

    return 0;
}

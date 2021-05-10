/**
 * 
 * Baekjoon 2579, 계단 오르기
 * 210510
 * https://www.acmicpc.net/problem/2579
 * 
*/
#include <iostream>
#include <vector>
using namespace std;

// 계단 오르기 게임은 계단 아래 시작점부터 계단 꼭대기에 위치한 도착점까지 가는 게임이다.

// 각 계단에 쓰여 있는 점수가 주어질 때 이 게임에서 얻을 수 있는 총 점수의 최댓값을 구하는 프로그램을 작성하시오.
int S;

// 각각의 계단에는 일정한 점수가 쓰여 있는데 계단을 밟으면 그 계단에 쓰여 있는 점수를 얻게 된다.
vector<int> stairs;

// 계단 오르는 데는 다음과 같은 규칙이 있다.
// 계단은 한 번에 한 계단씩 또는 두 계단씩 오를 수 있다.
// 연속된 세 개의 계단을 모두 밟아서는 안 된다. 
// 단, 시작점은 계단에 포함되지 않는다.
// 마지막 도착 계단은 반드시 밟아야 한다.
vector<int> dp;

int main(){
        
    // 입력의 첫째 줄에 계단의 개수가 주어진다.
    cin >> S;
    
    stairs.assign(S+1, 0);
    dp.assign(S+1, 0);
    // 둘째 줄부터 한 줄에 하나씩 제일 아래에 놓인 계단부터 순서대로 각 계단에 쓰여 있는 점수가 주어진다. 계단의 개수는 300이하의 자연수이고, 계단에 쓰여 있는 점수는 10,000이하의 자연수이다.
    for(int s = 1; s <= S; s++)
        cin >> stairs[s];

    // 첫째 줄에 계단 오르기 게임에서 얻을 수 있는 총 점수의 최댓값을 출력한다.
    dp[1] = stairs[1];
    dp[2] = stairs[1] + stairs[2];
    for(int s = 3; s <= S; s++)
        dp[s] = max(dp[s-2] + stairs[s], dp[s-3] + stairs[s-1] + stairs[s]);
    
    cout << dp.back() << '\n';

    return 0;
}

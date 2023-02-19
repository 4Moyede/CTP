/**
 * 
 * 백준 14501번, 퇴사
 * 200306
 * https://www.acmicpc.net/problem/14501
 * 
*/
#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

// 오늘부터 N+1일째 되는 날 퇴사를 하기 위해서, 남은 N일 동안 최대한 많은 상담을 하려고 한다.
int N;

// 각각의 상담은 상담을 완료하는데 걸리는 기간 Ti와 상담을 했을 때 받을 수 있는 금액 Pi로 이루어져 있다.
vector<int> Ti;
vector<int> Pi;

void DFS(int idx, int cnt);

// 상담을 적절히 했을 때, 백준이가 얻을 수 있는 최대 수익을 구하는 프로그램을 작성하시오.
int money = INT_MIN;

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    // 첫째 줄에 N (1 ≤ N ≤ 15)이 주어진다.
    cin >> N;

    // 둘째 줄부터 N개의 줄에 Ti와 Pi가 공백으로 구분되어서 주어지며, 1일부터 N일까지 순서대로 주어진다. (1 ≤ Ti ≤ 5, 1 ≤ Pi ≤ 1,000)
    Ti.assign(N, 0);
    Pi.assign(N, 0);
    
    for(int n = 0; n < N; n++)
        cin >> Ti[n] >> Pi[n];

    DFS(0, 0);

    // 첫째 줄에 백준이가 얻을 수 있는 최대 이익을 출력한다.
    cout << money << '\n';

    return 0;
}

// 상담을 하는데 필요한 기간은 1일보다 클 수 있기 때문에, 모든 상담을 할 수는 없다.
// 예를 들어서 1일에 상담을 하게 되면, 2일, 3일에 있는 상담은 할 수 없게 된다. 2일에 있는 상담을 하게 되면, 3, 4, 5, 6일에 잡혀있는 상담은 할 수 없다.
// 또한, N+1일째에는 회사에 없기 때문에, 6, 7일에 있는 상담을 할 수 없다.
void DFS(int idx, int cnt){
    
    money = max(cnt, money);

    for(int i = idx; i < N; i++){
        if(i + Ti[i] <= N){
            DFS(i + Ti[i], cnt + Pi[i]);
        }
    }
}
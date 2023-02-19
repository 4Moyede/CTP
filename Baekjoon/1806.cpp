/**
 * 
 *  백준 1806번, 부분합
 *  191214
 *  https://www.acmicpc.net/problem/1806
 * 
*/
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <vector>
using namespace std;

// 10,000 이하의 자연수로 이루어진 길이 N짜리 수열이 주어진다. 
int N;
vector<int> number;

// 이 수열에서 연속된 수들의 부분합 중에 그 합이 S 이상이 되는 것 중, 
int S;

// 가장 짧은 것의 길이를 구하는 프로그램을 작성하시오.
int ans = INT_MAX;
int sum = 0;

void solve();

int main(){

    cin.tie(NULL);  cin.sync_with_stdio(false);
    cout.tie(NULL); cout.sync_with_stdio(false);

    // 첫째 줄에 N (10 ≤ N < 100,000)과 S (0 < S ≤ 100,000,000)가 주어진다.
    cin >> N >> S;

    // 둘째 줄에는 수열이 주어진다. 수열의 각 원소는 공백으로 구분되어져 있으며, 10,000이하의 자연수이다.
    number.assign(N, 0);

    for(int n = 0; n < N; n++)
        cin >> number[n];

    solve();

    // 첫째 줄에 구하고자 하는 최소의 길이를 출력한다. 만일 그러한 합을 만드는 것이 불가능하다면 0을 출력하면 된다.
    if(ans == INT_MAX)
        cout << 0 << '\n';
    else
        cout << ans << '\n';
    
    return 0;
}

void solve(){
    int low = 0, high = 0;
    sum += number[0];

    //투 포인터 알고리즘 적용
    while (low <= high && high < N){
        if (sum < S)
            sum += number[++high];
        else if (sum == S){
            ans = min(ans, (high - low + 1));
            sum += number[++high];
        }
        else if (sum > S){
            ans = min(ans, (high - low + 1));
            sum -= number[low++];
        }
    }
}
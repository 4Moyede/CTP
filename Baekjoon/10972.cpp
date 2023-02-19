/**
 * 
 * 백준 10972번, 다음 순열
 * 190526
 * https://www.acmicpc.net/problem/10972
 * 
*/
#include <iostream>
#include <limits.h>
#include <vector>
#include <algorithm>
using namespace std;

// 1부터 N까지의 수로 이루어진 순열이 있다. 이때, 사전순으로 다음에 오는 순열을 구하는 프로그램을 작성하시오.
vector<int> v;

// 첫째 줄에 N(1 ≤ N ≤ 10,000)이 주어진다. 둘째 줄에 순열이 주어진다.
int N;

int main(){
    cin >> N;
    v.assign(N, -1);
    for(int i = 0; i < N; i++){
        cin >> v[i];
    }
    
    int change_s = -1;

    for(int i = 0; i < N-1; i++){
        if(v[i] < v[i+1])
            change_s = i;
    }

    // 만약, 사전순으로 마지막에 오는 순열인 경우에는 -1을 출력한다.
    if(change_s == -1){
        cout << "-1\n";
        return 0;
    }

    // 사전 순으로 가장 앞서는 순열은 오름차순으로 이루어진 순열이고, 가장 마지막에 오는 순열은 내림차순으로 이루어진 순열이다.
    int next_idx = change_s + 1;
    for(int i = change_s + 1; i < N; i++){
        if(v[change_s] < v[i] && v[next_idx] > v[i]){
            next_idx = i;
        }
    }
    swap(v[change_s], v[next_idx]);
    vector<int>::iterator iter_s = v.begin() + change_s + 1;
    sort(iter_s, v.end());

    // 첫째 줄에 입력으로 주어진 순열의 다음에 오는 순열을 출력한다. 
    for(int i = 0; i < N; i++){
        cout << v[i] << " ";
    }
    cout << "\n";

    return 0;
}
/**
 * 
 * 백준 10451번, 순열 사이클
 * 190514
 * https://www.acmicpc.net/problem/10451
 * 
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 각 테스트 케이스의 첫째 줄에는 순열의 크기 N (2 ≤ N ≤ 1,000)이 주어진다. 
int N;

// 순열 그래프 (3, 2, 7, 8, 1, 4, 5, 6) 에는 총 3개의 사이클이 있다. 이러한 사이클을 "순열 사이클" 이라고 한다.
vector<int> num;
vector<bool> visited;

void DFS(int idx);

// N개의 정수로 이루어진 순열이 주어졌을 때, 순열 사이클의 개수를 구하는 프로그램을 작성하시오.
int main(){

    // 첫째 줄에 테스트 케이스의 개수 T가 주어진다. 
    int testcase;
    cin >> testcase;

    for(int t = 0; t < testcase; ++t){
        int res = 0;
        cin >> N;
        num.assign(N+1, -1);
        visited.assign(N+1, false);
        // 둘째 줄에는 순열이 주어지며, 각 정수는 공백으로 구분되어 있다.
        for(int n = 1; n <= N; ++n){
            cin >> num[n];
        }

        for(int n = 1; n <= N; n++){
            if(!visited[n]){
                DFS(n);
                res++;
            }
        }

        // 각 테스트 케이스마다, 입력으로 주어진 순열에 존재하는 순열 사이클의 개수를 출력한다.
        cout << res << "\n";
    }

    return 0;
}

void DFS(int idx){
    visited[idx] = true;

    if(!visited[num[idx]])
        DFS(num[idx]);
}
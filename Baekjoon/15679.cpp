/**
 * 
 * 백준 15679번, N과 M(1)
 * 200118
 * https://www.acmicpc.net/problem/15679
 * 
*/
#include <iostream>
#include <vector>
using namespace std;

// 자연수 N과 M이 주어졌을 때, 
int N, M;

// 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성하시오.
bool check[9] = { false, };
vector<int> arr;

// 1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열
// 중복되는 수열을 여러 번 출력하면 안되며, 각 수열은 공백으로 구분해서 출력해야 한다.
// 수열은 사전 순으로 증가하는 순서로 출력해야 한다.
void DFS();

int main(){
    
    cin.tie(NULL);  cin.sync_with_stdio(false);
    cout.tie(NULL); cout.sync_with_stdio(false);

    // 첫째 줄에 자연수 N과 M이 주어진다. (1 ≤ M ≤ N ≤ 8)
    cin >> N >> M;

    // 한 줄에 하나씩 문제의 조건을 만족하는 수열을 출력한다.
    DFS();

    return 0;
}

void DFS(){
    if(arr.size() == M){
        for(int i = 0; i < M; i++)
            cout << arr[i] << ' ';
        cout << '\n';
        return;
    }

    for(int i = 0; i < N; i++){
        if(!check[i]){
            check[i] = true;
            arr.push_back(i+1);
            DFS();
            arr.pop_back();
            check[i] = false;
        }
    }
}
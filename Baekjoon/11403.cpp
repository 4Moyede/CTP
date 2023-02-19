/**
 * 
 * 백준 11403번, 경로 찾기
 * 191004
 * https://www.acmicpc.net/problem/11403
 * 
*/
#include <iostream>
#include <vector>
using namespace std;

// i번째 줄의 j번째 숫자가 1인 경우에는 i에서 j로 가는 간선이 존재한다는 뜻이고, 0인 경우는 없다는 뜻이다. 
// i번째 줄의 i번째 숫자는 항상 0이다.
int N;
vector<vector<int> > road;
vector<vector<int> > check;

// 정점 i에서 j로 가는 경로가 있으면 i번째 줄의 j번째 숫자를 1로, 없으면 0으로 출력해야 한다.
vector<vector<int> > ans;
int start_idx;

void solve();
void DFS(int idx);

// 모든 정점 (i, j)에 대해서, i에서 j로 가는 경로가 있는지 없는지 구하는 프로그램을 작성하시오.
int main(){

    // 첫째 줄에 정점의 개수 N (1 ≤ N ≤ 100)이 주어진다. 
    cin >> N;
    road.assign(N, vector<int>());
    check.assign(N, vector<int>());
    ans.assign(N, vector<int>(N, 0));

    // 둘째 줄부터 N개 줄에는 그래프의 인접 행렬이 주어진다. 
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            int temp;
            cin >> temp;

            if(temp){
                road[y].push_back(x);
                check[y].push_back(-1);
            }
        }
    }

    solve();

    // 총 N개의 줄에 걸쳐서 문제의 정답을 인접행렬 형식으로 출력한다.
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            cout << ans[y][x] << ' ';
        }
        cout << endl;
    }
    return 0;
}

void solve(){
    for(int n = 0; n < N; n++){
        start_idx = n;
        for(int i = 0; i < road[start_idx].size(); i++){
            check[start_idx][i] = start_idx;
            DFS(road[start_idx][i]);
            check[start_idx][i] = start_idx - 1;
        }
    }
}

void DFS(int idx){

    if(!ans[start_idx][idx]){
        ans[start_idx][idx] = 1;
    }

    for(int i = 0 ; i < road[idx].size(); i++){
        if(check[idx][i] == start_idx) continue;
        
        int next = road[idx][i];
        if(!ans[start_idx][next]){
            check[idx][i] = start_idx;
            DFS(next);
            check[idx][i] = start_idx - 1;
        }
    }
}
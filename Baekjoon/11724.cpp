/**
 * 
 * 백준 11724번, 연결 요소의 개수
 * 190515
 * https://www.acmicpc.net/problem/11724
 * 
*/
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

// 정점의 개수 N과 간선의 개수 M이 주어진다. (1 ≤ N ≤ 1,000, 0 ≤ M ≤ N×(N-1)/2) 
int N, M;

vector<vector<int> > dot;
vector<bool> visited;

void DFS(int idx);
void BFS(int idx);

// 방향 없는 그래프가 주어졌을 때, 연결 요소 (Connected Component)의 개수를 구하는 프로그램을 작성하시오.
int main(){
    // M개의 줄에 간선의 양 끝점 u와 v가 주어진다. (1 ≤ u, v ≤ N, u ≠ v) 같은 간선은 한 번만 주어진다.
    cin >> N >> M;
    dot.assign(N+1, vector<int>(0,0));
    visited.assign(N+1, false);

    for(int m = 0; m < M; m++){
        int _input1, _input2;
        cin >> _input1 >> _input2;
        dot[_input1].push_back(_input2);
        dot[_input2].push_back(_input1);
    }

    int ans = 0;
    for(int n = 1; n <= N; n++){
        if(!visited[n]){
            BFS(n);
            ans++;
        }
    }

    // 첫째 줄에 연결 요소의 개수를 출력한다.
    cout << ans << endl;
    return 0;
}

void DFS(int idx){

    if(visited[idx]) return;
    visited[idx] = true;
    
    for(int i = 0; i < dot[idx].size(); i++)
        DFS(dot[idx][i]);
}

void BFS(int idx){

    queue<int> q;
    q.push(idx);
    visited[idx] = true;

    while(!q.empty()){
        int cur = q.front();
        q.pop();

        for(int i = 0; i < dot[cur].size(); i++){
            int next = dot[cur][i];
            if(visited[next]) continue;
            visited[next] = true;
            q.push(next);
        }
    }

}
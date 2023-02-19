/**
 * 
 * 백준 2606번, 바이러스
 * 190513
 * https://www.acmicpc.net/problem/2606
 * 
*/
#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
using namespace std;

int com, conn;
vector<vector<int> > v;
vector<bool> visited;

void BFS();
void DFS(int idx);

// 컴퓨터의 수와 네트워크 상에서 서로 연결되어 있는 정보가 주어질 때, 1번 컴퓨터를 통해 웜 바이러스에 걸리게 되는 컴퓨터의 수를 출력하는 프로그램을 작성하시오.
int main(){

    // 첫째 줄에는 컴퓨터의 수가 주어진다. 컴퓨터의 수는 100 이하이고 각 컴퓨터에는 1번 부터 차례대로 번호가 매겨진다. 
    // 둘째 줄에는 네트워크 상에서 직접 연결되어 있는 컴퓨터 쌍의 수가 주어진다. 
    cin >> com >> conn;
    v.assign(com+1, vector<int>(0, 0));
    visited.assign(com+1, false);

    for(int c = 0; c < conn; c++){
        int input1_, input2_;
        // 이어서 그 수만큼 한 줄에 한 쌍씩 네트워크 상에서 직접 연결되어 있는 컴퓨터의 번호 쌍이 주어진다.
        cin >> input1_ >> input2_;
        v[input1_].push_back(input2_);
        v[input2_].push_back(input1_);
    }

    //BFS();
    DFS(1);
    
    int cnt = 0;
    for(int i = 2; i <= com; i++){
        if(visited[i])
            cnt++;
    }

    cout << cnt << "\n";

    return 0;
}

void BFS(){

    queue<int> q;
    // 1번 컴퓨터가 웜 바이러스에 걸렸다. 
    q.push(1);
    visited[1] = true;

    while(!q.empty()){
        int cur = q.front();
        q.pop();

        for(int i = 0; i < v[cur].size(); i++){
            if(!visited[v[cur][i]]){
                visited[v[cur][i]] = true;
                q.push(v[cur][i]);
            }
        }
    }

}

void DFS(int idx){

    if(visited[idx]) return;

    visited[idx] = true;

    for(int i = 0; i < v[idx].size(); i++){
        if(!visited[v[idx][i]])
            DFS(v[idx][i]);
    }

}
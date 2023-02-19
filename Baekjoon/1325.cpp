/**
 * 
 * 백준 1325번, 효율적인 해킹
 * 190514
 * https://www.acmicpc.net/problem/1325
 * 
*/
#include <iostream>
#include <limits.h>
#include <vector>
#include <algorithm>
using namespace std;

// N은 10,000보다 작거나 같은 자연수, M은 100,000보다 작거나 같은 자연수이다. 
int N, M;

// A가 B를 신뢰하는 경우에는 B를 해킹하면, A도 해킹할 수 있다는 소리다.
vector<vector<int> > com;
vector<bool> visited;
// visited를 false로 init 시켜주면서, 방문했던 노드의 갯수 return
int init_visited(); 

void DFS(int idx);

vector<int> compromised;
vector<int> weak_com;

// 한 번에 가장 많은 컴퓨터를 해킹할 수 있는 컴퓨터의 번호를 출력하는 프로그램을 작성하시오.
int main(){
    // 첫째 줄에, N과 M이 들어온다. 
    cin >> N >> M;

    // 컴퓨터는 1번부터 N번까지 번호가 하나씩 매겨져 있다.
    com.assign(N+1, vector<int>(0, 0));
    visited.assign(N+1, false);
    compromised.assign(N+1, -1);

    for(int m = 0; m < M; ++m){
        // 둘째 줄부터 M개의 줄에 신뢰하는 관계가 A B와 같은 형식으로 들어오며, "A가 B를 신뢰한다"를 의미한다. 
        int _input1, _input2;
        cin >> _input1 >> _input2;
        com[_input2].push_back(_input1); // 방향성이 있는 그래프
    }

    for(int n = 1; n <= N; ++n){
        DFS(n);
        compromised[n] = init_visited(); // visited를 false로 init 시켜주면서, 방문했던 노드의 갯수 return
    }

    // 한 번에 가장 많은 컴퓨터를 해킹할 수 있는 컴퓨터의 번호를 오름차순으로 출력한다.
    int largest = INT_MIN;
    for(int n = 1; n <= N; n++){
        if(largest < compromised[n]){
            weak_com.clear();
            largest = compromised[n];
            weak_com.push_back(n);
        }
        else if(largest == compromised[n]){
            weak_com.push_back(n);
        }
    }

    sort(weak_com.begin(), weak_com.end());
    for(int i = 0; i < weak_com.size(); ++i){
        cout << weak_com[i] << " ";
    }
    cout << "\n";
    return 0;
}

int init_visited(){
    int cnt = 0;
    for(int n = 1; n <= N; ++n){
        if(visited[n]){ 
            cnt++;
            visited[n] = false;
        }
    }

    return cnt;
}

void DFS(int idx){

    if(visited[idx]) return;
    visited[idx] = true;
    
    for(int i = 0; i < com[idx].size(); ++i){
        DFS(com[idx][i]);
    }
}
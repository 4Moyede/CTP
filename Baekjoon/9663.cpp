/**
 * 
 *  백준 9663번, N-Queen
 *  191008
 *  https://www.acmicpc.net/problem/9663
 * 
*/
#include <iostream>
using namespace std;

// N-Queen 문제는 크기가 N × N인 체스판 위에 퀸 N개를 서로 공격할 수 없게 놓는 문제이다.
// N이 주어졌을 때, 퀸을 놓는 방법의 수를 구하는 프로그램을 작성하시오.
int N;

void DFS(int idx, int cnt);
bool possible(int idx, int n);

int location[15];
int count = 0;
bool found = false;

int main(){
    // 첫째 줄에 N이 주어진다. (1 ≤ N < 15)
    cin >> N;

    DFS(0, 0);

    // 첫째 줄에 퀸 N개를 서로 공격할 수 없게 놓는 경우의 수를 출력한다.
    cout << count << endl;
    
    return 0;
}

void DFS(int idx, int cnt){

    if(cnt == N){
        count++;
        return;
    }

    for(int i = 0 ; i < N; i++){
        if(!possible(idx, i))   continue;
        
        location[idx] = i;
        DFS(idx+1, cnt+1);
        location[idx] = -1;
    }
}

bool possible(int idx, int n){

    for(int i = 0; i < idx; i++){
        if(location[i] == n)
            return false;
        if(abs(idx - i) == abs(location[i] - n))
            return false;
    }

    return true;
}
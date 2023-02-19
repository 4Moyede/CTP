/**
 * 
 * 백준 10026번, 적록색약
 * 191207
 * https://www.acmicpc.net/problem/10026
 * 
*/
#include <iostream>
using namespace std;

// 크기가 N×N인 그리드의 각 칸에 R(빨강), G(초록), B(파랑) 중 하나를 색칠한 그림이 있다. 
int N;
char map[101][101] = { 0, };

// 그림은 몇 개의 구역으로 나뉘어져 있는데, 구역은 같은 색으로 이루어져 있다.
// 또, 같은 색상이 상하좌우로 인접해 있는 경우에 두 글자는 같은 구역에 속한다.
// 색상의 차이를 거의 느끼지 못하는 경우도 같은 색상이라 한다.
void DFS(int c, int y, int x);

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };
int check[2][101][101] = { 0, };
int ans[2] = { 0, };

// 그림이 입력으로 주어졌을 때, 적록색약인 사람이 봤을 때와 아닌 사람이 봤을 때 구역의 수를 구하는 프로그램을 작성하시오.
int main(){

    // 첫째 줄에 N이 주어진다. (1 ≤ N ≤ 100)
    cin >> N;

    // 둘째 줄부터 N개 줄에는 그림이 주어진다.
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            cin >> map[y][x];
        }
    }

    for(int c = 0; c < 2; c++ ){
        for(int y = 0; y < N; y++){
            for(int x = 0; x < N; x++){
                if(check[c][y][x]) continue;
                ans[c]++;
                DFS(c, y, x);
            }
        }
    }

    // 적록색약이 아닌 사람이 봤을 때의 구역의 개수와 적록색약인 사람이 봤을 때의 구역의 수를 공백으로 구분해 출력한다.
    cout << ans[0] << " " << ans[1] << '\n';

    return 0;
}

void DFS(int c, int y, int x){

    check[c][y][x] = ans[c];

    for(int d = 0; d < 4; d++){
        int ny = y + dy[d];
        int nx = x + dx[d];

        if(ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
        if(check[c][ny][nx]) continue;
        
        if(map[y][x] != map[ny][nx]) {
            if(c){
                if(map[y][x] == 'B' || map[ny][nx] == 'B'){
                    continue;
                }
            }
            else{
                continue;
            }
        }

        DFS(c, ny, nx);
    }
}
/**
 * 
 * 백준 1012번, 유기농 배추
 * 190522
 * https://www.acmicpc.net/problem/1012
 * 
*/
#include <iostream>
using namespace std;

// 한 배추의 상하좌우 네 방향에 다른 배추가 위치한 경우에 서로 인접해있다고 간주한다
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

// 0은 배추가 심어져 있지 않은 땅이고, 1은 배추가 심어져 있는 땅을 나타낸다.
enum state { EMPTY = 0, PLANT = 1 };

// 배추를 심은 배추밭의 가로길이 M(1 ≤ M ≤ 50)과 세로길이 N(1 ≤ N ≤ 50), 
// 그리고 배추가 심어져 있는 위치의 개수 K(1 ≤ K ≤ 2500)이 주어진다. 
int M, N, K;

// 이 지렁이는 배추근처에 서식하며 해충을 잡아 먹음으로써 배추를 보호한다. 
// 어떤 배추에 배추흰지렁이가 한 마리라도 살고 있으면 이 지렁이는 인접한 다른 배추로 이동할 수 있다.
void DFS(int x, int y);

int map[51][51] = { EMPTY, };

int main(){
    // 입력의 첫 줄에는 테스트 케이스의 개수 T가 주어진다. 
    int testcase;
    cin >> testcase;

    for(int t = 0; t < testcase; t++){
        cin >> M >> N >> K;

        //그 다음 K줄에는 배추의 위치 X(0 ≤ X ≤ M-1), Y(0 ≤ Y ≤ N-1)가 주어진다.
        for(int k = 0; k < K; k++){
            int input_y, input_x;
            cin >> input_x >> input_y;
            map[input_y][input_x] = PLANT;
        }

        int cnt = 0;
        for(int y = 0; y < N; y++){
            for(int x = 0; x < M; x++){
                if(map[y][x] == PLANT){
                    DFS(y, x);
                    cnt++;
                }
            }
        }
        // 각 테스트 케이스에 대해 필요한 최소의 배추흰지렁이 마리 수를 출력한다.
        cout << cnt << "\n";
    }

    return 0;
}

void DFS(int y, int x){
    
    if(y < 0 || x < 0 || y >= N || x >= M) return;
    if(map[y][x] == EMPTY) return;

    map[y][x] = EMPTY;

    for(int dir = 0; dir < 4; dir++){
        int ny = y + dy[dir];
        int nx = x + dx[dir];

        DFS(ny, nx);
    }
}
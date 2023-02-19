/**
 * 
 * 백준 7576번, 토마토2
 * 190504
 * https://www.acmicpc.net/problem/7576
 * 
*/
#include <iostream>
#include <queue>
#include <utility>
#include <limits.h>
using namespace std;

// 첫 줄에는 상자의 크기를 나타내는 두 정수 M,N이 주어진다. M은 상자의 가로 칸의 수, N은 상자의 세로 칸의 수를 나타낸다.
int M, N;
// 단, 2 ≤ M,N ≤ 1,000 이다. 
int map[1002][1002];
int copy_map[1002][1002];

// 정수 1은 익은 토마토, 정수 0은 익지 않은 토마토, 정수 -1은 토마토가 들어있지 않은 칸을 나타낸다. 
enum tomato { EMPTY = -1, RAW, RIPE };

// 하나의 토마토의 인접한 곳은 왼쪽, 오른쪽, 앞, 뒤 네 방향에 있는 토마토를 의미한다. 
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

// 보관 후 하루가 지나면, 익은 토마토들의 인접한 곳에 있는 익지 않은 토마토들은 익은 토마토의 영향을 받아 익게 된다. 
// 철수는 창고에 보관된 토마토들이 며칠이 지나면 다 익게 되는지, 그 최소 일수를 알고 싶어 한다.
void BFS();
queue<pair<int, int> > q;
int cnt = -1;

int main() {

    cin >> M >> N;
    bool alreadyRipe = true;
    // 둘째 줄부터는 하나의 상자에 저장된 토마토들의 정보가 주어진다. 즉, 둘째 줄부터 N개의 줄에는 상자에 담긴 토마토의 정보가 주어진다. 
    for(int y = 0; y < N; y++){
        for(int x = 0; x < M; x++){
            cin >> map[y][x];
            copy_map[y][x] = map[y][x];
            if(alreadyRipe && map[y][x] != RIPE)
                alreadyRipe = false;
            if(map[y][x] == RIPE){
                q.push(make_pair(y, x));
            }
        }   
    }

    // 만약, 저장될 때부터 모든 토마토가 익어있는 상태이면 0을 출력해야 하고, 
    if(alreadyRipe){
        cnt = 0;
    }
    else{
        BFS();

        for(int y = 0; y < N; y++){
            for(int x = 0; x < M; x++){
                if(copy_map[y][x] == RAW)
                {
                    cout << "-1" << "\n";
                    return 0;
                }
                if(cnt < copy_map[y][x])
                    cnt = copy_map[y][x];
            }
        }
    }

    // 여러분은 토마토가 모두 익을 때까지의 최소 날짜를 출력해야 한다. 토마토가 모두 익지는 못하는 상황이면 -1을 출력해야 한다.
    cout << cnt - 1 << "\n";

    return 0;
}

void BFS(){

    while(!q.empty()){
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();

        int cur_value = copy_map[cur_y][cur_x];

        for(int dir = 0; dir < 4; dir++){
            int next_y = cur_y + dy[dir];
            int next_x = cur_x + dx[dir];

            if(next_x < 0 || next_x >= M || next_y < 0 || next_y >= N) continue;
            if(copy_map[next_y][next_x] != RAW) continue;

            copy_map[next_y][next_x] = cur_value + 1;
            
            q.push(make_pair(next_y, next_x));
        }
    }
}
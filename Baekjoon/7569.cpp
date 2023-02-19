/**
 * 
 * 백준 7569번, 토마토
 * 190507
 * https://www.acmicpc.net/problem/7569
 * 
*/
#include <iostream>
#include <queue>
#include <limits.h>
using namespace std;

// 정수 1은 익은 토마토, 정수 0 은 익지 않은 토마토, 정수 -1은 토마토가 들어있지 않은 칸을 나타낸다.
enum state { EMPTY = -1, RAW = 0, RIPE = 1 };

struct tomato{
    int z, y, x;
    state stat;
    bool visited;
    int day;

    void save(int _z, int _y, int _x, int _stat){ 
        z = _z; y = _y; x = _x;
        stat = (state)_stat;
        visited = false;
        day = 0;
    }
};

// 단, 2 ≤ M ≤ 100, 2 ≤ N ≤ 100, 1 ≤ H ≤ 100 이다. 
tomato map[101][101][101];

int X, Y, Z;

// 보관 후 하루가 지나면, 익은 토마토들의 인접한 곳에 있는 익지 않은 토마토들은 익은 토마토의 영향을 받아 익게 된다. 
// 하나의 토마토에 인접한 곳은 위, 아래, 왼쪽, 오른쪽, 앞, 뒤 여섯 방향에 있는 토마토를 의미한다. 
const int dx[] = { 0, 0, 0, 0, 1, -1 };
const int dy[] = { 0, 0, 1, -1, 0, 0 };
const int dz[] = { 1, -1, 0, 0, 0, 0 };

queue<tomato> q;
void bfs();
int cnt();

// 토마토가 모두 익을 때까지 최소 며칠이 걸리는지를 계산해서 출력해야 한다. 
// 만약, 저장될 때부터 모든 토마토가 익어있는 상태이면 0을 출력해야 하고, 토마토가 모두 익지는 못하는 상황이면 -1을 출력해야 한다.
int main()
{
    // 첫 줄에는 상자의 크기를 나타내는 두 정수 M,N과 쌓아올려지는 상자의 수를 나타내는 H가 주어진다. 
    // M은 상자의 가로 칸의 수, N은 상자의 세로 칸의 수를 나타낸다. 
    cin >> X >> Y >> Z;
    for(int z = 0; z < Z; z++){
        for(int y = 0; y < Y; y++){
            for(int x = 0; x < X; x++){
                int stat;
                cin >> stat;
                map[z][y][x].save(z, y, x, stat);

                if(stat == RIPE){
                    q.push(map[z][y][x]);
                    map[z][y][x].visited = true;
                    map[z][y][x].day = 1;
                }
                else if(stat == EMPTY)
                    map[z][y][x].day = -1;
            }
        }
    }

    bfs();

    cout << cnt() << "\n";

    return 0;
}

void bfs(){

    while(!q.empty()){
        tomato qFront = q.front();
        q.pop();

        int cur_z = qFront.z;
        int cur_y = qFront.y;
        int cur_x = qFront.x;

        for(int dir = 0; dir < 6; dir++){ // 6방향
            int next_z = cur_z + dz[dir];
            int next_y = cur_y + dy[dir];
            int next_x = cur_x + dx[dir];

            if(next_z < 0 || next_y < 0 || next_x < 0 || next_z >= Z || next_y >= Y || next_x >= X) continue; // 토마토 상자의 범위 밖
            if(map[next_z][next_y][next_x].stat != RAW) continue; // 익지않은 토마토가 아닌 경우
            if(map[next_z][next_y][next_x].visited) continue; // 이미 방문한 경우

            // 범위 안, RAW, not visited tomato 인 경우
            map[next_z][next_y][next_x].stat = RIPE;
            map[next_z][next_y][next_x].visited = true;
            map[next_z][next_y][next_x].day = map[cur_z][cur_y][cur_x].day + 1;
            q.push(map[next_z][next_y][next_x]);
        }
    }
}

int cnt(){

    int day = INT_MIN;
    for(int z = 0; z < Z; z++){
        for(int y = 0; y < Y; y++){
            for(int x = 0; x < X; x++){
                if(map[z][y][x].day > day)
                    day = map[z][y][x].day;
                if(map[z][y][x].day == 0) // day가 0이라는 것은, RAW인 토마토가 남았다는 것을 의미
                    return -1;
            }
        }
    }

    return day - 1; // RAW임에도 RIPE되지 못한 경우를 확인하기 위해, RIPE의 day를 1로 임의변경하였으므로 -1
}
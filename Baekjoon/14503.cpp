/**
 * 
 * 백준 14503번, 로봇 청소기
 * 190926
 * https://www.acmicpc.net/problem/14503
 * 
*/
#include <iostream>
#include <utility>
#include <queue>
using namespace std;

// 청소기는 바라보는 방향이 있으며, 이 방향은 동, 서, 남, 북중 하나이다. 
// d가 0인 경우에는 북쪽을, 1인 경우에는 동쪽을, 2인 경우에는 남쪽을, 3인 경우에는 서쪽을 바라보고 있는 것이다.
enum direction {NORTH = 0, EAST, SOUTH, WEST};

int dir_y[4] = {0, -1, 0, 1};
int dir_x[4] = {-1, 0, 1, 0};

struct machine {
    int y;
    int x;
    int d;
    bool visited = false;

    machine next(){
        machine n;
        switch(d){
            case NORTH:
                n.y = y;
                n.x = x - 1;
                n.d = WEST;
                break;
            case EAST:
                n.y = y - 1;
                n.x = x;
                n.d = NORTH;
                break;
            case SOUTH:
                n.y = y;
                n.x = x + 1;
                n.d = EAST;
                break;
            case WEST:
                n.y = y + 1;
                n.x = x;
                n.d = SOUTH;
                break;
        }

        return n;
    }

    machine back(){
        machine n;
        switch(d){
            case NORTH:
                n.y = y + 1;
                n.x = x;
                n.d = NORTH;
                break;
            case EAST:
                n.y = y;
                n.x = x - 1;
                n.d = EAST;
                break;
            case SOUTH:
                n.y = y - 1;
                n.x = x;
                n.d = SOUTH;
                break;
            case WEST:
                n.y = y;
                n.x = x + 1;
                n.d = WEST;
                break;
        }

        return n;
    }
};
machine start;

// 로봇 청소기가 있는 장소는 N×M 크기의 직사각형으로 나타낼 수 있으며, 1×1크기의 정사각형 칸으로 나누어져 있다. 
// 각각의 칸은 벽 또는 빈 칸이다. 
// 지도의 각 칸은 (y, x)로 나타낼 수 있고, y은 북쪽으로부터 떨어진 칸의 개수, x는 서쪽으로 부터 떨어진 칸의 개수이다.
int N, M;
int map[51][51] = { 0, };
machine visited[51][51];

queue<machine> q;

void print_(){
    cout << '\n';
    for(int y = 0 ; y < N; y++){
        for(int x = 0; x < M; x++){
            if(map[y][x] == 1)
                cout << "1 ";
            else{
                if(visited[y][x].visited)   
                    cout << "2 ";
                else
                    cout << "0 ";
            }
        }
        cout << '\n';
    }
    cout << '\n';
}

void BFS();

// 로봇 청소기가 주어졌을 때, 청소하는 영역의 개수를 구하는 프로그램을 작성하시오.
int main(){

    // 첫째 줄에 세로 크기 N과 가로 크기 M이 주어진다. (3 ≤ N, M ≤ 50)
    cin >> N >> M;

    // 둘째 줄에 로봇 청소기가 있는 칸의 좌표 (r, c)와 바라보는 방향 d가 주어진다.
    cin >> start.y >> start.x >> start.d;

    // 셋째 줄부터 N개의 줄에 장소의 상태가 북쪽부터 남쪽 순서대로, 각 줄은 서쪽부터 동쪽 순서대로 주어진다. 빈 칸은 0, 벽은 1로 주어진다. 장소의 모든 외곽은 벽이다.
    for(int y = 0; y < N; y++){
        for(int x = 0; x < M; x++){
            cin >> map[y][x];
        }
    }

    BFS();

    // 로봇 청소기가 청소하는 칸의 개수를 출력한다.
    int ans = 0;
    for(int y = 0; y < N; y++){
        for(int x = 0; x < M; x++){
            if(visited[y][x].visited)
                ans++;
        }
    }
    cout << ans << '\n';

    return 0;
}


void BFS(){

    q.push(start);
    
    // 로봇 청소기는 이미 청소되어있는 칸을 또 청소하지 않으며, 벽을 통과할 수 없다.
    // 로봇 청소기가 있는 칸의 상태는 항상 빈 칸이다.
    while(!q.empty()){
        machine cur = q.front();
        q.pop();

        // 현재 위치를 청소한다.
        cur.visited = true;
        visited[cur.y][cur.x] = cur;

        // 현재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색을 진행한다.
        machine next = cur.next();

        if(next.y < 0 || next.y > N || next.x < 0 || next.x > M){
            // 왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전하고 2번으로 돌아간다.
            next.y = cur.y;
            next.x = cur.x;
            q.push(next);
        }
        else if(map[next.y][next.x] == 1 || visited[next.y][next.x].visited){
            bool back = true;
            for(int dir = 0; dir < 4; dir++){
                int next_y = cur.y + dir_y[dir];
                int next_x = cur.x + dir_x[dir];
                if(next_y >= 0 && next_y <= N && next_x >= 0 && next_x <= M){
                    if(map[next_y][next_x] == 0){
                        if(!visited[next_y][next_x].visited){
                            back = false;
                            break;
                        }
                    }
                }
            }
            if(back){
                // 네 방향 모두 청소가 이미 되어있거나 벽인 경우에는, 바라보는 방향을 유지한 채로 한 칸 후진을 하고 2번으로 돌아간다.
                next = cur.back();
                // 네 방향 모두 청소가 이미 되어있거나 벽이면서, 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.
                if(map[next.y][next.x] != 1)
                    q.push(next);
            }
            else{
                next.y = cur.y;
                next.x = cur.x;
                q.push(next);
            }
        }
        else{
            // 왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 그 방향으로 회전한 다음 한 칸을 전진하고 1번부터 진행한다. 
            q.push(next);
        }
    }
}
/**
 * 
 * 백준 2178번, 미로 탐색
 * 190505
 * https://www.acmicpc.net/problem/2178
 * 
*/
#include <iostream>
#include <queue>
#include <utility>
#include <typeinfo>
using namespace std;

// N×M크기의 배열로 표현되는 미로가 있다.
int N, M;
char map[101][101];
int copy_map[101][101] = { 0, };

// 미로에서 1은 이동할 수 있는 칸을 나타내고, 0은 이동할 수 없는 칸을 나타낸다. 
enum space { WALL = '0', MOVE = '1' };

// 한 칸에서 다른 칸으로 이동할 때, 서로 인접한 칸으로만 이동할 수 있다.
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

int BFS();

int main()
{
    // (0, 0)에서 출발하여 (N, M)의 위치로 이동할 때 지나야 하는 최소의 칸 수를 구하는 프로그램을 작성하시오. 
    // 첫째 줄에 두 정수 N, M(2 ≤ N, M ≤ 100)이 주어진다. 
    cin >> N >> M;
    // 다음 N개의 줄에는 M개의 정수로 미로가 주어진다. 각각의 수들은 붙어서 입력으로 주어진다.
    for(int y = 0; y < N; ++y){
        for(int x = 0; x < M; ++x){
            cin >> map[y][x];
            copy_map[y][x] = 0;
        }
    }

    cout << BFS() << "\n";

    return 0;
}

int BFS(){
    queue<pair<int, int> > q;
    q.push(make_pair(0, 0));

    copy_map[0][0] = 1;

    while(!q.empty()){
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();

        for(int d = 0; d < 4; d++){
            int next_y = cur_y + dy[d];
            int next_x = cur_x + dx[d];

            if(next_y < 0 || next_x < 0 || next_y >= N || next_x >= M) continue; // 범위를 벗어나는 경우
            if(map[next_y][next_x] == WALL) continue; // 이동할 수 없는 지역인 경우
            if(copy_map[next_y][next_x] != 0) continue; // 이미 지난 지역인 경우
            
            q.push(make_pair(next_y, next_x));
            copy_map[next_y][next_x] = copy_map[cur_y][cur_x] + 1;
        }
    }

    return copy_map[N-1][M-1];
}
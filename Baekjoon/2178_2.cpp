/**
 * 
 * Baekjoon 2178, 미로 탐색
 * 210331
 * https://www.acmicpc.net/problem/2178
 * 
*/
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

// N×M크기의 배열로 표현되는 미로가 있다.
// 미로에서 1은 이동할 수 있는 칸을 나타내고, 0은 이동할 수 없는 칸을 나타낸다. 
int N, M;
int map[102][102];
int cnt_map[102][102];
bool visited[102][102];

// 이러한 미로가 주어졌을 때, (1, 1)에서 출발하여 (N, M)의 위치로 이동할 때 지나야 하는 최소의 칸 수를 구하는 프로그램을 작성하시오. 
void BFS();

// 한 칸에서 다른 칸으로 이동할 때, 서로 인접한 칸으로만 이동할 수 있다.
int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

//칸을 셀 때에는 시작 위치와 도착 위치도 포함한다.
int res = INT_MAX;

int main(){
    // 첫째 줄에 두 정수 N, M(2 ≤ N, M ≤ 100)이 주어진다. 다음 N개의 줄에는 M개의 정수로 미로가 주어진다. 각각의 수들은 붙어서 입력으로 주어진다.
    cin >> N >> M;
    for(int n = 0; n < N; n++){
        for(int m = 0; m < M; m++){
            scanf("%1d", &map[n][m]);
        }
    }

    BFS();

    // 첫째 줄에 지나야 하는 최소의 칸 수를 출력한다. 항상 도착위치로 이동할 수 있는 경우만 입력으로 주어진다.
    cout << res << '\n';

    return 0;
}

void BFS(){
    queue<pair<int, int> > q;
    q.push(make_pair(0, 0));
    cnt_map[0][0] = 1;

    while(!q.empty()){
        int curY = q.front().first;
        int curX = q.front().second;
        q.pop();

        for(int d = 0; d < 4; d++){
            int nextY = curY + dy[d];
            int nextX = curX + dx[d];

            if(nextY < 0 || nextY >= N || nextX < 0 || nextX >= M) continue;
            if(!map[nextY][nextX]) continue;
            if(cnt_map[nextY][nextX]) continue;

            cnt_map[nextY][nextX] = cnt_map[curY][curX] + 1;
            q.push(make_pair(nextY, nextX));
        }
    }

    res = cnt_map[N - 1][M - 1];
}
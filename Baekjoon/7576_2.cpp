/**
 * 
 * Baekjoon 7576, 토마토
 * 210331
 * https://www.acmicpc.net/problem/7576
 * 
*/
#include <iostream>
#include <utility>
#include <queue>
using namespace std;

// 토마토는 격자 모양 상자의 칸에 하나씩 넣어서 창고에 보관한다. 
int box[1000][1000];

// 창고에 보관되는 토마토들 중에는 잘 익은 것도 있지만, 아직 익지 않은 토마토들도 있을 수 있다. 
// 보관 후 하루가 지나면, 익은 토마토들의 인접한 곳에 있는 익지 않은 토마토들은 익은 토마토의 영향을 받아 익게 된다. 
queue<pair<int, int> > q;
void BFS();

// 하나의 토마토의 인접한 곳은 왼쪽, 오른쪽, 앞, 뒤 네 방향에 있는 토마토를 의미한다. 대각선 방향에 있는 토마토들에게는 영향을 주지 못하며, 토마토가 혼자 저절로 익는 경우는 없다고 가정한다. 
int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

// 철수는 창고에 보관된 토마토들이 며칠이 지나면 다 익게 되는지, 그 최소 일수를 알고 싶어 한다.
int days = 0;

// M은 상자의 가로 칸의 수, N은 상자의 세로 칸의 수를 나타낸다. 단, 2 ≤ M,N ≤ 1,000 이다. 
int M, N;

int main(){
    // 첫 줄에는 상자의 크기를 나타내는 두 정수 M,N이 주어진다. 
    cin >> M >> N;

    // 둘째 줄부터는 하나의 상자에 저장된 토마토들의 정보가 주어진다. 즉, 둘째 줄부터 N개의 줄에는 상자에 담긴 토마토의 정보가 주어진다. 
    // 하나의 줄에는 상자 가로줄에 들어있는 토마토의 상태가 M개의 정수로 주어진다. 
    // 정수 1은 익은 토마토, 정수 0은 익지 않은 토마토, 정수 -1은 토마토가 들어있지 않은 칸을 나타낸다.
    // 토마토가 하나 이상 있는 경우만 입력으로 주어진다.
    for(int n = 0; n < N; n++){
        for(int m = 0; m < M; m++){
            cin >> box[n][m];
            if(box[n][m] == 1)
                q.push(make_pair(n, m));
        }
    }

    BFS();

    // 여러분은 토마토가 모두 익을 때까지의 최소 날짜를 출력해야 한다. 만약, 저장될 때부터 모든 토마토가 익어있는 상태이면 0을 출력해야 하고, 토마토가 모두 익지는 못하는 상황이면 -1을 출력해야 한다.
    cout << days << '\n';

    return 0;
}

void BFS(){
    while(!q.empty()){
        int curY = q.front().first;
        int curX = q.front().second;
        q.pop();

        for(int d = 0; d < 4; d++){
            int nextY = curY + dy[d];
            int nextX = curX + dx[d];

            if(nextY < 0 || nextY >= N || nextX < 0 || nextX >= M)  continue;
            if(box[nextY][nextX] != 0) continue;
            
            box[nextY][nextX] = box[curY][curX] + 1;
            q.push(make_pair(nextY, nextX));
        }
    }
    
    for(int n = 0; n < N; n++){
        for(int m = 0; m < M; m++){
            if(box[n][m] == 0){
                days = -1;
                return;
            }
            days = max(days, box[n][m] - 1);   
        }
    }
}
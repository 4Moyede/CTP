/**
 * 
 * 백준 14502번, 연구소1
 * 190508
 * https://www.acmicpc.net/problem/14502
 * 
*/
#include <iostream>
#include <limits.h>
#include <queue>
#include <utility>
using namespace std;

// 첫째 줄에 지도의 세로 크기 N과 가로 크기 M이 주어진다. (3 ≤ N, M ≤ 8)
int N, M;
int map[9][9];
bool visited[9][9] = { false, };

const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

int BFS();
void init();

int main()
{
    cin >> N >> M;

    // 둘째 줄부터 N개의 줄에 지도의 모양이 주어진다. 
    // 0은 빈 칸, 1은 벽, 2는 바이러스가 있는 위치이다. 2의 개수는 2보다 크거나 같고, 10보다 작거나 같은 자연수이다.
    for(int y = 0; y < N; ++y){
        for(int x = 0; x < M; ++x){
            cin >> map[y][x];
        }
    }

    int ans = INT_MIN;

    for(int y1 = 0; y1 < N; y1++){
        for(int x1 = 0; x1 < M; x1++){
            if(map[y1][x1] != 0) continue;
            for(int y2 = 0; y2 < N; y2++){
                for(int x2 = 0; x2 < M; x2++){
                    if(map[y2][x2] != 0) continue;
                    if(y1 == y2 && x2 == x1) continue;
                    for(int y3 = 0; y3 < N; y3++){
                        for(int x3 = 0; x3 < M; x3++){
                            if(map[y3][x3] != 0) continue;
                            if((y1 == y3 && x1 == x3) || (y2 == y3 && x2 == x3)) continue;
                            map[y1][x1] = map[y2][x2] = map[y3][x3] = 1;
                            ans = max(BFS(), ans);
                            map[y1][x1] = map[y2][x2] = map[y3][x3] = 0;
                        }
                    }
                }
            }
        }
    }

    cout << ans << "\n";

    return 0;
}

int BFS(){

    int copy_map[9][9];
    queue<pair<int, int> > q;

    for(int y = 0; y < N; ++y){
        for(int x = 0; x < M; ++x){
            copy_map[y][x] = map[y][x];
            visited[y][x] = false;
            if(map[y][x] == 2){
                visited[y][x] = true;
                q.push(make_pair(y, x));
            }
        }
    }

    while(!q.empty()){
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();

        for(int d = 0; d < 4; d++){
            int next_y = cur_y + dy[d];
            int next_x = cur_x + dx[d];

            if(next_y < 0 || next_y >= N || next_x < 0 || next_x >= M) continue; // 범위를 벗어나는 경우
            if(copy_map[next_y][next_x] != 0) continue; // 빈칸이 아닌 경우
            if(visited[next_y][next_x]) continue;  // 이미 방문한 경우

            visited[next_y][next_x] = true;
            copy_map[next_y][next_x] = 2;
            q.push(make_pair(next_y, next_x));
        }
    }


    // 첫째 줄에 얻을 수 있는 안전 영역의 최대 크기를 출력한다.
    int cnt = 0;
    for(int y = 0; y < N; ++y){
        for(int x = 0; x < M; ++x){
            if(copy_map[y][x] == 0)
                cnt++;
        }
    }
    
    return cnt;
}
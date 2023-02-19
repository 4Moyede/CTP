/**
 * 
 * 백준 17141번, 연구소2
 * 190509
 * https://www.acmicpc.net/problem/17141
 * 
*/
#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

// 연구소의 크기 N(5 ≤ N ≤ 50), 놓을 수 있는 바이러스의 개수 M(1 ≤ M ≤ 10)이 주어진다.
int N, M;

// 연구소는 크기가 N×N인 정사각형으로 나타낼 수 있으며, 정사각형은 1×1 크기의 정사각형으로 나누어져 있다. 
int map[51][51];
int copy_map[51][51];
bool visited[51][51] = { false, };

queue<pair<int, int> > q;
vector<pair<int, int> > v;
bool check[11] = { false, };

// 바이러스는 상하좌우로 인접한 모든 빈 칸으로 모두 복제되며, 1초가 걸린다.
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

// 0은 빈 칸, 1은 벽, 2는 바이러스를 놓을 수 있는 위치이다. 2의 개수는 M보다 크거나 같고, 10보다 작거나 같은 자연수이다.
enum space { WALL = -2, BLANK = -1, VIRUS = 1 };

// 연구소의 상태가 주어졌을 때, 모든 빈 칸에 바이러스를 퍼뜨리는 최소 시간을 구해보자.
int ans = INT_MAX;

void DFS(int idx, int cnt);
int BFS();

int main()
{
    cin >> N >> M;
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            cin >> map[y][x];
            if(map[y][x] == 2) // Virus를 놓을 수 있는 위치 vector에 저장
                v.push_back(make_pair(y, x));
        }
    }

    DFS(0, 0);

    // 바이러스를 어떻게 놓아도 모든 빈 칸에 바이러스를 퍼뜨릴 수 없는 경우에는 -1을 출력한다.
    if (ans == INT_MAX) ans = -1; // ans 가 INT_MAX 라는 건, 모든 BFS에서 바이러스의 전체 확산이 실패했음을 의미

    // 연구소의 모든 빈 칸에 바이러스가 있게 되는 최소 시간을 출력한다. 
    cout << ans << "\n";

    return 0;
}

void DFS(int idx, int cnt){
    
    if(idx > v.size()) return;

    // 조건 만족
    if(cnt == M){

        // copy_map Setting
        for(int y = 0; y < N; y++){
            for(int x = 0; x < N; x++){
                if(map[y][x] == 0){
                    copy_map[y][x] = BLANK;
                    visited[y][x] = false;
                }
                else if(map[y][x] == 1){
                    copy_map[y][x] = WALL;
                    visited[y][x] = false;
                }
                else {
                    copy_map[y][x] = BLANK;
                    visited[y][x] = false;
                }
                
            }
        } 

        // check된 좌표 VIRUS로 설정
        for(int i = 0; i < v.size(); i++){
            if(check[i]){
                copy_map[v[i].first][v[i].second] = VIRUS;
                visited[v[i].first][v[i].second] = true;
                q.push(make_pair(v[i].first, v[i].second));
            }
            else{
                copy_map[v[i].first][v[i].second] = BLANK;
                visited[v[i].first][v[i].second] = false;
            }
        }

        // BFS 실행
        ans = min(ans, BFS());
    }
    
    // DFS
    for(int i = idx; i < v.size(); i++){
        check[i] = true;
        DFS(i + 1, cnt + 1);
        check[i] = false;
    }

}

int BFS(){

    while(!q.empty()){

        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; dir++){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];

            if(ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
            if(copy_map[ny][nx] != BLANK) continue;
            if(visited[ny][nx]) continue;

            copy_map[ny][nx] = copy_map[cy][cx] + 1;
            visited[ny][nx] = true;
            q.push(make_pair(ny, nx));
        }
    }

    int large = INT_MIN;
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            if(large < copy_map[y][x])
                large = copy_map[y][x];
            if(copy_map[y][x] == BLANK)
                return INT_MAX; // INT_MAX 값을 리턴, min(ans, BFS()) 를 무조건 ans가 되도록 한다.
        }
    }

    return large - 1;
}
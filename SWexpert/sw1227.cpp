/**
 * 
 * SW Expert 1227번, 미로2
 * 190512
 * https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV14wL9KAGkCFAYD
 * 
*/
#include <iostream>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

#define width       100
#define testcase    10

// 16*16 행렬의 형태로 만들어진 미로
char map[width+1][width+1];
bool visited[width+1][width+1] = { false, };

const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

vector<int> result;
queue<pair<int, int> > q;
int BFS();

// 주어진 미로의 출발점으로부터 도착지점까지 갈 수 있는 길이 있는지 판단하는 프로그램을 작성하라.
int main(){

    for(int t = 0; t < testcase; t++){
        pair<int, int> start;
        pair<int, int> end;

        int out;
        cin >> out;

        // visited init
        for(int y = 0; y < width; ++y){
            for(int x = 0; x < width; ++x){
                visited[y][x] = false;
            }
        }

         // 1은 벽을 나타내며 0은 길, 2는 출발점, 3은 도착점을 나타낸다.
        for(int y = 0; y < width; ++y){
            for(int x = 0; x < width; ++x){
                cin >> map[y][x];
                if(map[y][x] == '2'){
                    start = make_pair(y, x);
                    q.push(start);
                    visited[y][x] = true;
                }
                else if(map[y][x] == '3'){
                    end = make_pair(y, x);
                }
            }
        }

        BFS();

        // #부호와 함께 테스트 케이스의 번호를 출력하고, 공백 문자 후 도달 가능 여부를 1 또는 0으로 표시한다 
        // (1 - 가능함, 0 - 가능하지 않음)
        cout << "#" << t+1 << " " << visited[end.first][end.second] << "\n";
    }

    return 0;
}

int BFS(){

    while(!q.empty()){
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; dir++){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];

            if(ny < 0 || nx < 0 || ny >= width || nx >= width) continue;
            if(visited[ny][nx]) continue;
            if(map[ny][nx] == '1') continue;
            map[ny][nx] = 2;
            visited[ny][nx] = true;
            q.push(make_pair(ny, nx));
        }

    }
}
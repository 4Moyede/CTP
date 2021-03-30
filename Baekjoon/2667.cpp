/**
 * 
 * Baekjoon 2667, 단지번호붙이기
 * 210330
 * https://www.acmicpc.net/problem/2667
 * 
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// 정사각형 모양의 지도가 있다. 
int map[25][25];
bool visited[25][25];

// 1은 집이 있는 곳을, 0은 집이 없는 곳을 나타낸다. 
// 철수는 이 지도를 가지고 연결된 집의 모임인 단지를 정의하고, 단지에 번호를 붙이려 한다. 
// 여기서 연결되었다는 것은 어떤 집이 좌우, 혹은 아래위로 다른 집이 있는 경우를 말한다. 대각선상에 집이 있는 경우는 연결된 것이 아니다. 
int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

// 지도를 입력하여 단지수를 출력하고,
// 각 단지에 속하는 집의 수를 오름차순으로 정렬하여 출력하는 프로그램을 작성하시오.
vector<int> building;

void BFS(int sy, int sx);

// 첫 번째 줄에는 지도의 크기 N(정사각형이므로 가로와 세로의 크기는 같으며 5≤N≤25)이 입력되고, 그 다음 N줄에는 각각 N개의 자료(0혹은 1)가 입력된다.
int N;

int main(){
    cin >> N;

    for(int n = 0; n < N; n++){
        for(int m = 0; m < N; m++){
            scanf("%1d", &map[n][m]);
            visited[n][m] = false;
        }
    }

    for(int n = 0; n < N; n++){
        for(int m = 0; m < N; m++){
            if(visited[n][m]) continue;
            visited[n][m] = true;

            if(!map[n][m]) continue;

            BFS(n, m);
        }
    }

    // 첫 번째 줄에는 총 단지수를 출력하시오. 그리고 각 단지내 집의 수를 오름차순으로 정렬하여 한 줄에 하나씩 출력하시오.
    sort(building.begin(), building.end());
    cout << building.size() << '\n';
    for(int b = 0; b < building.size(); b++)
        cout << building[b] << '\n';

    return 0;
}

void BFS(int sy, int sx){
    queue<pair<int, int> > q;
    q.push(make_pair(sy, sx));

    int buildingArea = 0;

    while(!q.empty()){
        int curY = q.front().first;
        int curX = q.front().second;
        q.pop();

        buildingArea++;

        for(int d = 0; d < 4; d++){
            int nextY = curY + dy[d];
            int nextX = curX + dx[d];

            if(nextY < 0 || nextY >= N || nextX < 0 || nextX >= N) continue;
            if(visited[nextY][nextX]) continue;
            if(!map[nextY][nextX]) continue;
            
            visited[nextY][nextX] = true;
            
            q.push(make_pair(nextY, nextX));
        }
    }

    building.push_back(buildingArea);
}
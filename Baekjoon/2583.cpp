/**
 *
 *  백준 2583번, 영역 구하기
 *  191005
 *  https://www.acmicpc.net/problem/2583
 *
 */
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

// 눈금의 간격이 1인 M×N(M,N≤100)크기의 모눈종이가 있다. 
int M, N;

// 이 모눈종이 위에 눈금에 맞추어 K개의 직사각형을 그릴 때, 이들 K개의 직사각형의 내부를 제외한 나머지 부분이 몇 개의 분리된 영역으로 나누어진다.
int K; 

// K개의 직사각형 내부를 제외한 나머지 부분이 몇 개의 분리된 영역으로 나누어지는지, 
// 그리고 분리된 각 영역의 넓이가 얼마인지를 구하여 이를 출력하는 프로그램을 작성하시오.
vector<int> ans;

// 모눈종이의 왼쪽 아래 꼭짓점의 좌표는 (0,0)이고, 오른쪽 위 꼭짓점의 좌표는(N,M)이다. 입력되는 K개의 직사각형들이 모눈종이 전체를 채우는 경우는 없다.
vector<vector<int> > map;
vector<vector<int> > visited;

int dy[] = {0, 0, 1, -1};
int dx[] = {1, -1, 0, 0};

void BFS();

int main(){
    // 첫째 줄에 M과 N, 그리고 K가 빈칸을 사이에 두고 차례로 주어진다.  M, N, K는 모두 100 이하의 자연수이다. 
    cin >> M >> N >> K;
    map.assign(M, vector<int>(N, 0));
    visited.assign(M, vector<int>(N, 0));

    // 둘째 줄부터 K개의 줄에는 한 줄에 하나씩 직사각형의 왼쪽 아래 꼭짓점의 x, y좌표값과 
    // 오른쪽 위 꼭짓점의 x, y좌표값이 빈칸을 사이에 두고 차례로 주어진다.
    for(int k = 0; k < K; k++){
        int y_ld, x_ld, y_ru, x_ru;
        cin >> x_ld >> y_ld >> x_ru >> y_ru;

        for(int y = y_ld; y < y_ru; y++){
            for(int x = x_ld; x < x_ru; x++){
                map[y][x] = 1;
            }
        }
    }

    BFS();
    
    // 첫째 줄에 분리되어 나누어지는 영역의 개수를 출력한다. 둘째 줄에는 각 영역의 넓이를 오름차순으로 정렬하여 빈칸을 사이에 두고 출력한다.
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}

void BFS(){
    for(int y = 0; y < M; y++){
        for(int x = 0; x < N; x++){
            if(!map[y][x] && !visited[y][x]){
                queue<pair<int, int> > q;

                q.push(make_pair(y, x));
                visited[y][x] = 1;
                int cal = 0;

                while(!q.empty()){
                    int _y = q.front().first;
                    int _x = q.front().second;
                    q.pop();

                    cal++;

                    for(int i = 0; i < 4; i++){
                        int _ny = _y + dy[i];
                        int _nx = _x + dx[i];

                        if(_ny >= M || _ny < 0 || _nx >= N || _nx < 0)  continue;
                        if(map[_ny][_nx] == 1)                          continue;
                        if(visited[_ny][_nx] == 1)                      continue;
                       
                        visited[_ny][_nx] = 1;
                        q.push(make_pair(_ny, _nx));
                    }
                }
                ans.push_back(cal);
            }
        }
    }
}

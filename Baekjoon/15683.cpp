/**
 * 
 * 백준 15683번, 감시
 * 200306
 * https://www.acmicpc.net/problem/15683
 * 
*/
#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

// 스타트링크의 사무실은 1×1크기의 정사각형으로 나누어져 있는 N×M 크기의 직사각형으로 나타낼 수 있다. 
// 지도에서 0은 빈 칸, 6은 벽, 1~5는 CCTV의 번호이다.
int N, M;
int map[9][9] = { 0, };

// 사무실에는 총 K개의 CCTV가 설치되어져 있는데, 
int K;

// CCTV는 5가지 종류가 있다. 각 CCTV가 감시할 수 있는 방법은 다음과 같다.
// 1번 CCTV는 한 쪽 방향만 감시할 수 있다. 
// 2번과 3번은 두 방향을 감시할 수 있는데, 2번은 감시하는 방향이 서로 반대방향이어야 하고, 3번은 직각 방향이어야 한다. 
// 4번은 세 방향, 5번은 네 방향을 감시할 수 있다.
struct cctv {
    int number = 0;
    int y = -1;
    int x = -1;

    int status = -1;

    // CCTV는 회전시킬 수 있는데, 회전은 항상 90도 방향으로 해야 하며, 감시하려고 하는 방향이 가로 또는 세로 방향이어야 한다.
    bool turn_able(){
        switch(number){
            case 1:
            case 3:
            case 4:
                if(status < 4)
                    return true;
            case 2:
                if(status < 2)
                    return true;
            default:
                return false;
        }

        return false;
    }
};

// CCTV의 최대 개수는 8개를 넘지 않는다.
vector<cctv> cctvs;

void DFS(int idx);

// CCTV가 감시할 수 없는 영역은 사각지대라고 한다.
// 사무실의 크기와 상태, 그리고 CCTV의 정보가 주어졌을 때, CCTV의 방향을 적절히 정해서, 사각 지대의 최소 크기를 구하는 프로그램을 작성하시오.
void cnt_blindspot();
int ans = INT_MAX;

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    // 첫째 줄에 사무실의 세로 크기 N과 가로 크기 M이 주어진다. (1 ≤ N, M ≤ 8)
    cin >> N >> M;

    // 둘째 줄부터 N개의 줄에는 사무실 각 칸의 정보가 주어진다. 0은 빈 칸, 6은 벽, 1~5는 CCTV를 나타내고, 문제에서 설명한 CCTV의 종류이다. 
    for(int n = 0; n < N; n++){
        for(int m = 0; m < M; m++){
            cin >> map[n][m];
            if(map[n][m] > 0 && map[n][m] < 6){
                cctv cur = { map[n][m], n, m, 0 };
                cctvs.push_back(cur);
            }
        }
    }

    DFS(0);

    // 첫째 줄에 사각 지대의 최소 크기를 출력한다.
    cout << ans << '\n';
    
    return 0;
}

void DFS(int idx){

    cnt_blindspot();

    for(int i = idx; i < cctvs.size(); i++){
        if(cctvs[i].turn_able()){
            cctvs[i].status++;
            DFS(i);
            cctvs[i].status--;
        }
    }
}

void cnt_blindspot(){

    bool check[9][9] = { false, };

    for(int i = 0; i < cctvs.size(); i++){
        cctv start = cctvs[i];
        vector<pair<int, int> > d;

        // CCTV는 감시할 수 있는 방향에 있는 칸 전체를 감시할 수 있다. 
        switch(start.number){
            case 1:
                switch(start.status){
                    case 0:
                        d.push_back(make_pair(0, 1));
                        break;
                    case 1:
                        d.push_back(make_pair(1, 0));
                        break;
                    case 2:
                        d.push_back(make_pair(0, -1));
                        break;
                    case 3:
                        d.push_back(make_pair(-1, 0));
                        break;
                }
                break;

            case 2:
                switch(start.status){
                    case 0:
                        d.push_back(make_pair(0, 1));
                        d.push_back(make_pair(0, -1));
                        break;
                    case 1:
                        d.push_back(make_pair(1, 0));
                        d.push_back(make_pair(-1, 0));
                        break;
                }
                break;

            case 3:
                switch(start.status){
                    case 0:
                        d.push_back(make_pair(0, 1));
                        d.push_back(make_pair(1, 0));
                        break;
                    case 1:
                        d.push_back(make_pair(1, 0));
                        d.push_back(make_pair(0, -1));
                        break;
                    case 2:
                        d.push_back(make_pair(0, -1));
                        d.push_back(make_pair(-1, 0));
                        break;
                    case 3:
                        d.push_back(make_pair(-1, 0));
                        d.push_back(make_pair(0, 1));
                        break;
                }                    
                break;

            case 4:
                switch(start.status){
                    case 0:
                        d.push_back(make_pair(1, 0));
                        d.push_back(make_pair(0, 1));
                        d.push_back(make_pair(-1, 0));
                        break;
                    case 1:
                        d.push_back(make_pair(0, -1));
                        d.push_back(make_pair(1, 0));
                        d.push_back(make_pair(0, 1));
                        break;
                    case 2:
                        d.push_back(make_pair(-1, 0));
                        d.push_back(make_pair(0, -1));
                        d.push_back(make_pair(1, 0));
                        break;
                    case 3:
                        d.push_back(make_pair(0, 1));
                        d.push_back(make_pair(-1, 0));
                        d.push_back(make_pair(0, -1));
                        break;
                }
                break;

            case 5:
                d.push_back(make_pair(0, 1));
                d.push_back(make_pair(0, -1));
                d.push_back(make_pair(1, 0));
                d.push_back(make_pair(-1, 0));
                break;

        }

        for(int dir = 0; dir < d.size(); dir++){
            queue<cctv> q;
            q.push(start);

            int dy = d[dir].first;
            int dx = d[dir].second;
        
            while(!q.empty()){
                cctv cur_q = q.front();
                q.pop();

                int ny = cur_q.y + dy;
                int nx = cur_q.x + dx;

                if(ny < 0 || ny >= N || nx < 0 || nx >= M) continue;
                if(map[ny][nx] == 6) continue;  // CCTV는 벽을 통과할 수 없다.
                
                // CCTV는 CCTV를 통과할 수 있다.
                if(map[ny][nx] == 0) {
                    check[ny][nx] = true;
                }

                cctv next = { cur_q.number, ny, nx, cur_q.status };
                q.push(next);
            }
        }
    }

    int cnt = 0;
    for(int y = 0; y < N; y++){
        for(int x = 0; x < M; x++){
            if(check[y][x]) continue;
            if(map[y][x] > 0) continue;
            cnt++;
        }
    }

    ans = min(ans, cnt);
}
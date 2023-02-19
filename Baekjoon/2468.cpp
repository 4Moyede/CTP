/**
 * 
 * 백준 2468번, 안전영역
 * 190519
 * https://www.acmicpc.net/problem/2468
 * 
*/
#include <iostream>
#include <limits.h>
using namespace std;

// 첫째 줄에는 어떤 지역을 나타내는 2차원 배열의 행과 열의 개수를 나타내는 수 N이 입력된다. N은 2 이상 100 이하의 정수이다. 
int N;

// 둘째 줄부터 N개의 각 줄에는 2차원 배열의 첫 번째 행부터 N번째 행까지 순서대로 한 행씩 높이 정보가 입력된다. 
int map[101][101] = { 0, };
bool safe[101][101] = { false, };
int max_height = INT_MIN;

const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

void DFS(int y, int x);
int ans = INT_MIN;

// 어떤 지역의 높이 정보가 주어졌을 때, 장마철에 물에 잠기지 않는 안전한 영역의 최대 개수를 계산하는 프로그램을 작성하시오. 
int main(){

    cin >> N;
    // 각 줄에는 각 행의 첫 번째 열부터 N번째 열까지 N개의 높이 정보를 나타내는 자연수가 빈 칸을 사이에 두고 입력된다. 높이는 1이상 100 이하의 정수이다.
    for(int y = 0; y < N; ++y){
        for(int x = 0; x < N; ++x){
            cin >> map[y][x];
            if(map[y][x] > max_height)
                max_height = map[y][x];
        }
    }

    for(int rain = 1; rain <= max_height; rain++){
        for(int y = 0; y < N; y++){
            for(int x = 0; x < N; x++){
                if(rain <= map[y][x]){
                    safe[y][x] = true;
                }
                else{
                    safe[y][x] = false;
                }   
            }
        }
        
        int cnt = 0;
        for(int y = 0; y < N; y++){
            for(int x = 0; x <N; x++){
                if(safe[y][x]){
                    DFS(y, x);
                    cnt++;
                }
            }
        }

        ans = max(ans, cnt);
    }

    // 첫째 줄에 장마철에 물에 잠기지 않는 안전한 영역의 최대 개수를 출력한다.
    cout << ans << "\n";

    return 0;
}

void DFS(int y, int x){

    if(y < 0 || x < 0 || y >= N || x >= N) return;
    if(!safe[y][x]) return;

    safe[y][x] = false;
    
    for(int dir = 0; dir < 4; dir++){
        int ny = y + dy[dir];
        int nx = x + dx[dir];

        DFS(ny, nx);
    }

}
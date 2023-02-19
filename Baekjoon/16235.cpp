/**
 * 
 * 백준 16235번, 나무 제태크
 * 200310
 * https://www.acmicpc.net/problem/16235
 * 
*/
#include <iostream>
#include <list>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

// N×N 크기의 땅. 땅을 1×1 크기의 칸으로 나누어 놓았다. 
// 각각의 칸은 (r, c)로 나타내며, r은 가장 위에서부터 떨어진 칸의 개수, c는 가장 왼쪽으로부터 떨어진 칸의 개수이다. r과 c는 1부터 시작한다.
int N;
int map[12][12];
int food[12][12];

// S2D2는 1×1 크기의 칸에 들어있는 양분을 조사해 상도에게 전송하고, 모든 칸에 대해서 조사를 한다. 
// 가장 처음에 양분은 모든 칸에 5만큼 들어있다.
// M개의 나무를 구매해 땅에 심었다. 
// 같은 1×1 크기의 칸에 여러 개의 나무가 심어져 있을 수도 있다.
int M;
struct tree {
    pair<int, int> location;
    int age;
    bool alive;

    bool operator<(const tree &t){

        if(location.first < t.location.first){
            return true;
        }
        else if(location.first == t.location.first){
            if(location.second < t.location.second){
                return true;
            }
            else if(location.second == t.location.second){
                if(age < t.age){
                    return true;
                }
            }
        }
        return false;

    }

};
queue<tree> trees;
queue<tree> new_generation;
queue<tree> dead;
queue<tree> old;

// 봄에는 나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가한다.
// 각각의 나무는 나무가 있는 1×1 크기의 칸에 있는 양분만 먹을 수 있다.
// 하나의 칸에 여러 개의 나무가 있다면, 나이가 어린 나무부터 양분을 먹는다.
// 만약, 땅에 양분이 부족해 자신의 나이만큼 양분을 먹을 수 없는 나무는 양분을 먹지 못하고 즉시 죽는다.
void spring();

// 여름에는 봄에 죽은 나무가 양분으로 변하게 된다.
// 각각의 죽은 나무마다 나이를 2로 나눈 값이 나무가 있던 칸에 양분으로 추가된다. 소수점 아래는 버린다.
void summer();

// 가을에는 나무가 번식한다.
// 번식하는 나무는 나이가 5의 배수이어야 하며, 인접한 8개의 칸에 나이가 1인 나무가 생긴다.
// 상도의 땅을 벗어나는 칸에는 나무가 생기지 않는다.
void autumn();

// 겨울에는 S2D2가 땅을 돌아다니면서 땅에 양분을 추가한다. 
// 각 칸에 추가되는 양분의 양은 A[r][c]이고, 입력으로 주어진다.
void winter();

// K년이 지난 후 상도의 땅에 살아있는 나무의 개수를 구하는 프로그램을 작성하시오.
int K;

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    // 첫째 줄에 N, M, K가 주어진다.
    cin >> N >> M >> K;

    // 둘째 줄부터 N개의 줄에 A배열의 값이 주어진다. r번째 줄의 c번째 값은 A[r][c]이다.
    for(int y = 1; y <= N; y++){
        for(int x = 1; x <= N; x++){
            map[y][x] = 5;
            cin >> food[y][x];
        }
    }

    // 다음 M개의 줄에는 상도가 심은 나무의 정보를 나타내는 세 정수 x, y, z가 주어진다. 
    // 처음 두 개의 정수는 나무의 위치 (x, y)를 의미하고, 마지막 정수는 그 나무의 나이를 의미한다.
    for(int m = 0; m < M; m++){
        tree cur;
        cin >> cur.location.first >> cur.location.second >> cur.age;
        cur.alive = true;
        trees.push(cur);
    }

    for(int year = 0; year < K; year++){
        spring();
        summer();
        autumn();
        winter();
    }

    // 첫째 줄에 K년이 지난 후 살아남은 나무의 수를 출력한다.
    cout << trees.size() + new_generation.size() << '\n';

    return 0;
}

void spring(){

    bool stop = false;
    queue<tree> next;

    while(!stop){
        tree cur;
        if(!new_generation.empty()){
            cur = new_generation.front();
            new_generation.pop();
        }
        else{
            if(!trees.empty()){
                cur = trees.front();
                trees.pop();
            }
            else{
                stop = true;
                continue;
            }
        }

        int cy = cur.location.first;
        int cx = cur.location.second;

        if(map[cy][cx] >= cur.age){
            map[cy][cx] -= cur.age;
            cur.age++;
            next.push(cur);

            if(cur.age % 5 == 0)
                old.push(cur);
        }
        else{
            dead.push(cur);
        }
    }
    
    while(!next.empty()){
        trees.push(next.front());
        next.pop();
    }
    
}

void summer(){

    while(!dead.empty()){
        tree cur = dead.front();
        dead.pop();

        map[cur.location.first][cur.location.second] += (cur.age / 2);
    }

}

void autumn(){

    while(!old.empty()){
        tree cur = old.front();
        old.pop();

        int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
        int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
        for(int d = 0; d < 8; d++){
            int ny = cur.location.first + dy[d];
            int nx = cur.location.second + dx[d];
            if(ny < 1 || ny > N || nx < 1 || nx > N) continue;

            tree baby = { make_pair(ny, nx), 1, true };
            new_generation.push(baby);
        }
    }

}

void winter(){

    for(int y = 1; y <= N; y++){
        for(int x = 1; x <= N; x++){
            map[y][x] += food[y][x];
        }
    }

}
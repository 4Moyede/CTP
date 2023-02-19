/**
 * 
 * 백준 7562번, 나이트의 이동
 * 191207
 * https://www.acmicpc.net/problem/7562
 * 
*/
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

// 체스판 위에 한 나이트가 놓여져 있다. 
// 나이트가 이동하려고 하는 칸이 주어진다. 나이트는 몇 번 움직이면 이 칸으로 이동할 수 있을까?
int l, testcase;
pair<int, int> knight;
pair<int, int> dest;

int dy[] = { 2, 2, 1, -1, -2, -2, -1, 1 };
int dx[] = { -1, 1, 2, 2, 1, -1, -2, -2 };

void BFS();

int main(){
    // 입력의 첫째 줄에는 테스트 케이스의 개수가 주어진다.
    cin >> testcase;

    for(int t = 0 ; t < testcase; t++){

        // 첫째 줄에는 체스판의 한 변의 길이 l(4 ≤ l ≤ 300)이 주어진다. 
        cin >> l;
        
        // 둘째 줄과 셋째 줄에는 나이트가 현재 있는 칸, 나이트가 이동하려고 하는 칸이 주어진다.
        cin >> knight.first >> knight.second;
        cin >> dest.first >> dest.second;

        // 각 테스트 케이스마다 나이트가 몇 번만에 이동할 수 있는지 출력한다.
        BFS();
    }

    return 0;
}

void BFS(){
    // 체스판의 크기는 l × l이다. 
    int map[301][301] = { 0, };
    queue< pair<int, int> > q;

    // set knight position
    map[knight.first][knight.second] = 1;
    q.push(knight);

    while(!q.empty()){
        
        pair<int, int> cur = q.front();
        q.pop();
        int y = cur.first;
        int x = cur.second;

        // arrive
        if(cur == dest){
            // start number is 1
            cout << map[y][x] - 1 << '\n';
            break;
        }

        for(int n = 0; n < 8; n++){
            int ny = y + dy[n];
            int nx = x + dx[n];

            // out of map
            if(ny < 0 || ny >= l || nx < 0 || nx >= l) continue;
            // already been there
            if(map[ny][nx]) continue;

            // next
            map[ny][nx] = map[y][x] + 1;
            q.push(make_pair(ny, nx));
        }

    }

    // init map
    for(int y = 0; y < l; y++){
        for(int x = 0; x < l; x++){
            map[y][x] = 0;
        }
    }
}
/**
 * 
 * Baekjoon 7562, 나이트의 이동
 * 210401
 * https://www.acmicpc.net/problem/7562
 * 
*/

#include <iostream>
#include <utility>
#include <queue>
using namespace std;

// 체스판 위에 한 나이트가 놓여져 있다.
int dy[] = { 2, 2, 1, 1, -1, -1, -2, -2 };
int dx[] = { -1, 1, -2, 2, -2, 2, -1, 1 };

// 나이트가 이동하려고 하는 칸이 주어진다. 나이트는 몇 번 움직이면 이 칸으로 이동할 수 있을까?
int BFS(int length, pair<int, int> night, pair<int, int> target);

int main(){
    int T;
    // 입력의 첫째 줄에는 테스트 케이스의 개수가 주어진다.
    cin >> T;

    // 각 테스트 케이스는 세 줄로 이루어져 있다.
    for(int t = 0; t < T; t++){
        int l, res;
        pair<int, int> night, target;

        // 첫째 줄에는 체스판의 한 변의 길이 l(4 ≤ l ≤ 300)이 주어진다. 체스판의 크기는 l × l이다. 
        // 체스판의 각 칸은 두 수의 쌍 {0, ..., l-1} × {0, ..., l-1}로 나타낼 수 있다. 
        cin >> l;
        // 둘째 줄과 셋째 줄에는 나이트가 현재 있는 칸, 나이트가 이동하려고 하는 칸이 주어진다.
        cin >> night.first >> night.second;
        cin >> target.first >> target.second;

        res = BFS(l, night, target);
        // 각 테스트 케이스마다 나이트가 최소 몇 번만에 이동할 수 있는지 출력한다.
        cout << res << '\n';
    }

    return 0;
}

int BFS(int length, pair<int, int> night, pair<int, int> target){
    int map[300][300] = { 0, };
    queue<pair<int, int> > q;
    
    q.push(night);
    map[night.first][night.second] = 1;
    
    while(!q.empty()){
        int curY = q.front().first;
        int curX = q.front().second;
        q.pop();

        if(curY == target.first && curX == target.second){
            return map[curY][curX] - 1;
        }

        for(int d = 0; d < 8; d++){
            int nextY = curY + dy[d];
            int nextX = curX + dx[d];

            if(nextY < 0 || nextY >= length || nextX < 0 || nextX >= length)  continue;
            if(map[nextY][nextX])   continue;

            map[nextY][nextX] = map[curY][curX] + 1;
            q.push(make_pair(nextY, nextX));
        }
    }

    return -1;
}
/**
 * 
 *  백준 1987번, 알파벳
 *  191017
 *  https://www.acmicpc.net/problem/1987
 * 
*/
#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// 세로 R칸, 가로 C칸으로 된 표 모양의 보드가 있다. 보드의 각 칸에는 대문자 알파벳이 하나씩 적혀 있고, 좌측 상단 칸 (1행 1열) 에는 말이 놓여 있다.
int R, C;
char map[21][21];

// 말은 상하좌우로 인접한 네 칸 중의 한 칸으로 이동할 수 있는데, 새로 이동한 칸에 적혀 있는 알파벳은 지금까지 지나온 모든 칸에 적혀 있는 알파벳과는 달라야 한다. 즉, 같은 알파벳이 적힌 칸을 두 번 지날 수 없다.
int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };

void DFS(pair<int, int> cur, int cnt, vector<int> ch);

// 좌측 상단에서 시작해서, 말이 최대한 몇 칸을 지날 수 있는지를 구하는 프로그램을 작성하시오. 말이 지나는 칸은 좌측 상단의 칸도 포함된다.
int ans = INT_MIN;

int main(){

    // 첫째 줄에 R과 C가 빈칸을 사이에 두고 주어진다. (1<=R,C<=20) 둘째 줄부터 R개의 줄에 걸쳐서 보드에 적혀 있는 C개의 대문자 알파벳들이 빈칸 없이 주어진다.
    cin >> R >> C;
    for(int y = 0; y < R; y++)
        cin >> map[y];

    vector<int> ch(26, 0);

    DFS(make_pair(0, 0), 0, ch);

    // 첫째 줄에 말이 지날 수 있는 최대의 칸 수를 출력한다.
    cout << ans << '\n';

    return 0;
}

void DFS(pair<int, int> cur, int cnt, vector<int> ch){
    int cy = cur.first;
    int cx = cur.second;

    ch[map[cy][cx] - 'A'] = 1;
    if(ans < ++cnt)   ans = cnt;

    for(int n = 0; n < 4; n++){
        int ny = cy + dy[n];
        int nx = cx + dx[n];

        if(ny < 0 || ny >= R || nx < 0 || nx >= C) continue;
        if(ch[map[ny][nx] - 'A']) continue;

        DFS(make_pair(ny, nx), cnt, ch);
    }
}
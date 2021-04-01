/**
 * 
 * Baekjoon 14226, 이모티콘
 * 210401
 * https://www.acmicpc.net/problem/14226
 * 
*/
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

#define MAX 2000

struct status{
    short screen;
    short clipboard;
    short cnt;

    status(short _screen, short _clipboard, short _cnt) : screen(_screen), clipboard(_clipboard), cnt(_cnt) {};
};

bool visited[MAX][MAX] = { 0, };

// 효빈이에게 스마일 이모티콘을 S개 보내려고 한다.
int S;

// 영선이가 S개의 이모티콘을 화면에 만드는데 걸리는 시간의 최솟값을 구하는 프로그램을 작성하시오.
int res;

void BFS();

int main(){
    // 첫째 줄에 S (2 ≤ S ≤ 1000) 가 주어진다.
    cin >> S;

    BFS();

    // 첫째 줄에 이모티콘을 S개 만들기 위해 필요한 시간의 최솟값을 출력한다.
    cout << res << '\n';

    return 0;
}

void BFS(){
    queue<status> q;
    // 영선이는 이미 화면에 이모티콘 1개를 입력했다.
    q.push(status(1, 0, 0));

    while(!q.empty()){
        status curStatus = q.front();
        q.pop();

        if(curStatus.screen == S){
            res = curStatus.cnt;
            return;
        }

        // 이제, 다음과 같은 3가지 연산만 사용해서 이모티콘을 S개 만들어 보려고 한다.
        if(curStatus.clipboard){
            // 클립보드에 있는 모든 이모티콘을 화면에 붙여넣기 한다.
            // 화면에 이모티콘을 붙여넣기 하면, 클립보드에 있는 이모티콘의 개수가 화면에 추가된다.
            // 클립보드가 비어있는 상태에는 붙여넣기를 할 수 없으며, 일부만 클립보드에 복사할 수는 없다.
            int nextScreen = curStatus.screen + curStatus.clipboard;
            int nextClipboard = curStatus.clipboard;
            if(nextScreen < MAX && nextClipboard < MAX){
                if(!visited[nextScreen][nextClipboard]){
                    visited[nextScreen][nextClipboard] = true;
                    q.push(status(nextScreen, nextClipboard, curStatus.cnt + 1));
                }
            }
        }
        if(curStatus.screen){
            // 화면에 있는 이모티콘 중 하나를 삭제한다.
            int nextScreen = curStatus.screen - 1;
            int nextClipboard = curStatus.clipboard;
            if(nextScreen < MAX && nextClipboard < MAX){
                if(!visited[nextScreen][nextClipboard]){
                    visited[nextScreen][nextClipboard] = true;
                    q.push(status(nextScreen, nextClipboard, curStatus.cnt + 1));
                }
            }
            // 화면에 있는 이모티콘을 모두 복사해서 클립보드에 저장한다.
            // 클립보드에 이모티콘을 복사하면 이전에 클립보드에 있던 내용은 덮어쓰기가 된다. 
            // 또한, 클립보드에 있는 이모티콘 중 일부를 삭제할 수 없다.
            nextScreen = curStatus.screen;
            nextClipboard = curStatus.screen;
            if(nextScreen < MAX && nextClipboard < MAX){
                if(!visited[nextScreen][nextClipboard]){
                    visited[nextScreen][nextClipboard] = true;
                    q.push(status(nextScreen, nextClipboard, curStatus.cnt + 1));
                }
            }
        }
    }


}
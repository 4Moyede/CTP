/**
 * 
 * 백준 1697번, 숨바꼭질
 * 190515
 * https://www.acmicpc.net/problem/1697
 * 
*/
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

// 수빈이는 현재 점 N(0 ≤ N ≤ 100,000)에 있고, 동생은 점 K(0 ≤ K ≤ 100,000)에 있다. 
int N, K;

bool visited[100002] = { false, };

// 만약, 수빈이의 위치가 X일 때 걷는다면 1초 후에 X-1 또는 X+1로 이동하게 된다. 
// 순간이동을 하는 경우에는 1초 후에 2*X의 위치로 이동하게 된다.
void BFS();
int ans = 0;

// 수빈이와 동생의 위치가 주어졌을 때, 수빈이가 동생을 찾을 수 있는 가장 빠른 시간이 몇 초 후인지 구하는 프로그램을 작성하시오.
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL),  cout.tie(NULL);

    // 첫 번째 줄에 수빈이가 있는 위치 N과 동생이 있는 위치 K가 주어진다. N과 K는 정수이다.
    cin >> N >> K;

    BFS();

    // 수빈이가 동생을 찾는 가장 빠른 시간을 출력한다.
    cout << ans << "\n";

    return 0;
}

void BFS(){
    queue<pair<int, int> > q;
    q.push(make_pair(N, 0));
    visited[N] = true;

    while(!q.empty()){
        int cur = q.front().first;
        int cnt = q.front().second;
        q.pop();

        if(cur == K) {
            ans = cnt;
            break;
        }
        if(cur < 0 || cur > 100000) continue;

        if(cur+1 <= 100000 && !visited[cur+1]){
            q.push(make_pair(cur+1, cnt+1));
            visited[cur+1] = true;
        }
        if(cur-1 >= 0 && !visited[cur-1]){
            q.push(make_pair(cur-1, cnt+1));
            visited[cur-1] = true;
        }
        if(cur*2 <= 100000 && !visited[cur*2]){
            q.push(make_pair(cur*2, cnt+1));
            visited[cur*2] = true;
        }
    }
}
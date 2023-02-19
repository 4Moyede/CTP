/**
 * 
 *  백준 10216번, Count Circle Groups
 *  190513
 *  https://www.acmicpc.net/problem/10216 
 * 
*/
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

// 각 적군의 진영들은 진영마다 하나의 통신탑을 설치해, i번째 적군의 통신탑은 설치 위치로부터 Ri 이내 거리에 포함되는 모든 지역을 자신의 통신영역 Ai로 가지게 된다. 
// 이어서 N줄에 걸쳐 적군 진영의 좌표 x, y (0 ≤ x, y ≤ 5,000), 그리고 해당 진영의 R (0 ≤ R ≤ 5,000)이 주어진다. 주어지는 수는 모두 정수이다.
struct enermy{
    int x, y;
    int R;
    bool visited = false;
};

// 만약 임의의 통신영역 Ai와 Aj가 닿거나 겹치는 부분이 있다면 진영 i와 진영 j는 직접적으로 통신이 가능하다. 
// 물론 직접적으로 통신이 가능하지 않더라도, 임의의 지역 i와 j가 중간에 몇 개의 직접통신을 거쳐서 최종적으로 통신이 가능하다면 i와 j는 상호간에 통신이 가능한 것으로 본다.
// 상호간에 통신이 가능한 부대끼리는 결집력있는 한 그룹처럼 행동한다.
queue<enermy> q;
void BFS(int n);

// 2차원 평면 위의 N곳에 적군의 진영이 설치되어 있다.
vector<enermy> v;
// 각 테스트 케이스에 대해서 한 줄에 걸쳐 적군 진영의 그룹 개수를 출력한다.
vector<int> res;

// 각각의 테스트 케이스에 대해서 적군 진영의 숫자 N (1 ≤ N ≤ 3,000)이 주어진다. 
int N;

int main(){

    // 입력 파일의 첫 번째 줄에 테스트 케이스의 수를 의미하는 자연수 T가 주어진다. 그 다음에는 T개의 테스트 케이스가 주어진다.
    int testcase;
    cin >> testcase;
    for(int t = 0; t < testcase; t++){

        cin >> N;
        int cnt = 0;
        v.clear();
        for(int n = 0; n < N; n++){
            enermy new_;
            cin >> new_.x >> new_.y >> new_.R;
            new_.visited = false;
            v.push_back(new_);
        }

        for(int n = 0; n < N; n++){
            if(!v[n].visited){
                BFS(n);
                cnt++;
            }
        }

        res.push_back(cnt);
    }

    for(int i = 0; i < res.size(); i++){
        cout << res[i] << "\n";
    }
    return 0;
}

void BFS(int n){

    v[n].visited = true;
    q.push(v[n]);

    while(!q.empty()){
        enermy cur = q.front();
        q.pop();

        for(int i = 0; i < v.size(); i++){
            if(v[i].visited) continue;
            if(pow((cur.x - v[i].x), 2) + pow((cur.y - v[i].y), 2) <= pow((cur.R + v[i].R), 2)) {
                v[i].visited = true;
                q.push(v[i]);
            }
        }
    }

}
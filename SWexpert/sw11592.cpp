/**
 * 
 * SW Expert 11592번, 크루즈 컨트롤
 * 210320
 * https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AXfRhBl6KTMDFAS5
 * 
*/
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// 종로거리는 Dkm의 길이를 가지며, 흥부네는 0km 지점에서 동쪽으로 드라이브를 시작한다. 종로거리에는 현재 N마리의 다른 말들이 있으며 모두 동쪽으로 움직인다. 
// 이 때, N은 1 혹은 2이다.
int D, N;

// 이 중 i번째 말은 현재 Ki 킬로미터 지점에 있으며 맨 처음 Si km/시간 의 속도로 움직인다. 
vector<pair<int, int> > vehicle;
int totalTime = 0;

// 절대 다른 사람을 추월하지 않는다. 
// 각 사람을 종로거리 위의 크기가 없는 점이라고 생각하자. 
// 만약 현재 앞에 있는 사람의 속도가 자신보다 느리다면, 늦게 온 사람은 앞에 있는 사람의 속도에 맞춰서 느리게 주행한다.

// 흥부네는 크루즈 컨트롤 기능을 이용하여 종로거리 Dkm을 주행하려고 한다. 
// 크루즈 컨트롤 기능을 사용하면, 흥부네는 고정된 속도를 자율주행차에 입력할 수 있고, 자율주행차는 이 속도에 맞춰서 주행을 시작한다. 
// 흥부는 다른 말을 추월하거나 속도를 줄이고 싶지 않아서, 이러한 일이 없는 한 최고 속도로 주행하려고 한다. 가능한 속도는 얼마인가?
int speed();

// 첫 번째 줄에 테스트 케이스의 수 TC가 주어진다. 이후 TC개의 테스트 케이스가 새 줄로 구분되어 주어진다. 각 테스트 케이스는 다음과 같이 구성되었다.
int T;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL),  cout.tie(NULL);

    cin >> T;

    for(int t = 0; t < T; t++){
        // ∙ 첫 번째 줄에 두 정수 D, N이 주어진다. (1≤D≤109, 1≤N≤2)
        cin >> D >> N;
        // ∙ 이후 N개의 줄에 두 정수 Ki, Si가 주어진다(0 < Ki < D, 1 ≤ Si ≤ 10000). 모든 Ki는 서로 다르다.
        totalTime = 0;
        vehicle.clear();
        for (int n = 0; n < N; n++){
            int Ki, Si;
            cin >> Ki >> Si;
            vehicle.push_back(make_pair(Ki, Si));
        }
        // 각 테스트 케이스 마다 결과를 출력하라. 절대 오차 혹은 상대 오차가 10-5이하일 경우 통과된다.
        cout << "#" << t+1 << " " << speed() << '\n';
    }

    return 0;
}

int speed(){
    while(vehicle[0].first < D){
        for(int v = N-1; v >= 0; v--){
            if(v != 0){
                vehicle[v].first += vehicle[v].second;
            }
        }
        totalTime++;
    }
    double speed = D / totalTime;

    return speed;
}
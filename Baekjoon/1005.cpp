/**
 * 
 * Baekjoon 1005, ACM Craft
 * 210511
 * https://www.acmicpc.net/problem/1005
 * 
*/
#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// 첫 번째 게임과 두 번째 게임이 건물을 짓는 순서가 다를 수도 있다. 
// 매 게임시작 시 건물을 짓는 순서가 주어진다. 또한 모든 건물은 각각 건설을 시작하여 완성이 될 때까지 Delay가 존재한다.
// 건설순서는 모든 건물이 건설 가능하도록 주어진다.

vector<int> cost;
vector< vector<int> > build_next;
vector<int> build_need;

map<int, int> total_cost;

int dp(int start){
    queue<int> q;
    for(int idx = 0; idx < build_need.size(); idx++)
        if(!build_need[idx])
            q.push(idx);

    while(!q.empty()){
        int cur = q.front();
        q.pop();

        for(int idx = 0; idx < build_next[cur].size(); idx++){
            int next = build_next[cur][idx];
            total_cost[next] = max(total_cost[next], total_cost[cur] + cost[next]);
            build_need[next]--;

            if(!build_need[next])
                q.push(next);
        }
    }

    return total_cost[start];
}

int main(){
    
    // 첫째 줄에는 테스트케이스의 개수 T가 주어진다. 
    int T;
    cin >> T;

    for(int t = 0; t < T; t++){
        int N, K, W;
        cost.clear(); build_next.clear(); build_need.clear(); total_cost.clear();

        // 각 테스트 케이스는 다음과 같이 주어진다. 첫째 줄에 건물의 개수 N 과 건물간의 건설순서규칙의 총 개수 K이 주어진다.
        cin >> N >> K;
        cost.assign(N + 1, -1);
        build_next.assign(N + 1, vector<int>(0, 0));
        build_need.assign(N + 1, 0);

        // 둘째 줄에는 각 건물당 건설에 걸리는 시간 D가 공백을 사이로 주어진다. 
        for(int n = 1; n <= N; n++){
            cin >> cost[n];
            total_cost[n] = cost[n];
        }
        
        // 셋째 줄부터 K+2줄까지 건설순서 X Y가 주어진다. (이는 건물 X를 지은 다음에 건물 Y를 짓는 것이 가능하다는 의미이다) 
        for(int k = 0; k < K; k++){
            int X, Y;
            cin >> X >> Y;

            build_next[X].push_back(Y);
            build_need[Y]++;
        }

        // 마지막 줄에는 백준이가 승리하기 위해 건설해야 할 건물의 번호 W가 주어진다.
        cin >> W;

        // 건물 W를 건설완료 하는데 드는 최소 시간을 출력한다. 편의상 건물을 짓는 명령을 내리는 데는 시간이 소요되지 않는다고 가정한다.
        cout << dp(W) << '\n';
    }


    return 0;
}

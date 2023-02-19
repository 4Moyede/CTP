/**
 * 
 * 백준 15686번, 치킨 배달
 * 200309
 * https://www.acmicpc.net/problem/15686
 * 
*/
#include <iostream>
#include <utility>
#include <vector>
#include <limits.h>
using namespace std;

// 크기가 N×N인 도시가 있다. 도시는 1×1크기의 칸으로 나누어져 있다.
int N, M;

// 도시의 칸은 (r, c)와 같은 형태로 나타내고, r과 c는 1부터 시작한다.
int map[52][52];

// 0은 빈 칸, 1은 집, 2는 치킨집이다.
// 집의 개수는 2N개를 넘지 않으며, 적어도 1개는 존재한다. 
// 치킨집의 개수는 M보다 크거나 같고, 13보다 작거나 같다.
enum space { BLANK = 0, HOUSE = 1, CHICKEN = 2 };
struct chicken {
    pair<int, int> location;
    bool open;
};
vector<chicken> chickens;
vector<pair<int, int> > houses;

// 치킨 거리는 집과 가장 가까운 치킨집 사이의 거리이다. 
// 도시의 치킨 거리는 모든 집의 치킨 거리의 합이다.
int cal_distence(pair<int, int> a, pair<int, int> b);

// 도시에 있는 치킨집 중에서 최대 M개를 고르고, 나머지 치킨집은 모두 폐업시켜야 한다.
// 어떻게 고르면, 도시의 치킨 거리가 가장 작게 될지 구하는 프로그램을 작성하시오.
void DFS(int idx, int cnt);
void sum_distence();

int ans = INT_MAX;

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    // 첫째 줄에 N(2 ≤ N ≤ 50)과 M(1 ≤ M ≤ 13)이 주어진다.
    cin >> N >> M;

    // 둘째 줄부터 N개의 줄에는 도시의 정보가 주어진다.
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            cin >> map[y][x];
            switch(map[y][x]){
                case HOUSE:
                    houses.push_back(make_pair(y, x));
                    break;
                case CHICKEN:
                    chicken cur = { make_pair(y, x), false };
                    chickens.push_back(cur);
                    break;
            }
        }
    }

    DFS(0, 0);

    // 첫째 줄에 폐업시키지 않을 치킨집을 최대 M개를 골랐을 때, 도시의 치킨 거리의 최솟값을 출력한다.
    cout << ans << '\n';

    return 0;
}

int cal_distence(pair<int, int> a, pair<int, int> b){
 
    // 임의의 두 칸 (r1, c1)과 (r2, c2) 사이의 거리는 |r1-r2| + |c1-c2|로 구한다.
    return abs(a.first - b.first) + abs(a.second - b.second);

}

void DFS(int idx, int cnt){

    if(cnt > M) return;

    sum_distence();
    
    for(int i = idx; i < chickens.size(); i++){
        chickens[i].open = true;
        DFS(i + 1, cnt + 1);
        chickens[i].open = false;
    }

}

void sum_distence(){
    
    int cnt = 0;
    for(int h = 0; h < houses.size(); h++){
        int cur = INT_MAX;
        for(int c = 0; c < chickens.size(); c++){
            if(chickens[c].open){
                cur = min(cur, cal_distence(houses[h], chickens[c].location));
            }
        }
        if(cur != INT_MAX)
            cnt += cur;
    }

    if(cnt != 0)
        ans = min(ans, cnt);
}

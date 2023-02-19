/**
 * 
 *  백준 14889번, 스타트와 링크
 *  191212
 *  https://www.acmicpc.net/problem/14889
 * 
*/
#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

// 축구를 하기 위해 모인 사람은 총 N명이고 신기하게도 N은 짝수이다. 
// 이제 N/2명으로 이루어진 스타트 팀과 링크 팀으로 사람들을 나눠야 한다.
int N;

// 능력치 Sij는 i번 사람과 j번 사람이 같은 팀에 속했을 때, 팀에 더해지는 능력치이다. 
// 팀의 능력치는 팀에 속한 모든 쌍의 능력치 Sij의 합이다. 
// Sij는 Sji와 다를 수도 있으며, i번 사람과 j번 사람이 같은 팀에 속했을 때, 팀에 더해지는 능력치는 Sij와 Sji이다.
int stat[21][21] = { 0, }; 
bool check[21] = { false, };

// 스타트 팀의 능력치와 링크 팀의 능력치의 차이를 최소로 하려고 한다. 
int ans = INT_MAX;

void DFS(int idx, int cnt);

int main(){
    // 첫째 줄에 N(4 ≤ N ≤ 20, N은 짝수)이 주어진다. 
    cin >> N;

    // 둘째 줄부터 N개의 줄에 S가 주어진다. 
    // 각 줄은 N개의 수로 이루어져 있고, i번 줄의 j번째 수는 Sij 이다. 
    // Sii는 항상 0이고, 나머지 Sij는 1보다 크거나 같고, 100보다 작거나 같은 정수이다.
    for(int y = 0; y < N; y++)
        for(int x = 0; x < N; x++)
            cin >> stat[y][x];

    DFS(0, 0);

    // 첫째 줄에 스타트 팀과 링크 팀의 능력치의 차이의 최솟값을 출력한다.
    cout << ans << '\n';

    return 0;
}

void DFS(int idx, int cnt){
    if(cnt == N/2){
        vector<int> start_v;
        vector<int> link_v;

        for(int i = 0; i < N; i++){
            if(check[i])
                start_v.push_back(i);
            else
                link_v.push_back(i);
        }
        int start = 0;
        int link = 0;

        for(int i = 0; i < N/2; i++){
            for(int j = 0; j < N/2; j++){
                start += stat[start_v[i]][start_v[j]];
                link += stat[link_v[i]][link_v[j]];
            }
        }

        int cur = abs(start - link);
        if( ans > cur )
            ans = cur;

        return;
    }

    for(int i = idx; i < N; i++){
        check[i] = true;
        DFS(i+1, cnt+1);
        check[i] = false;
    }
}

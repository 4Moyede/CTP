/**
 * 
 * 백준 7567번, 그릇
 * 190520
 * https://www.acmicpc.net/problem/7567
 * 
*/
#include <iostream>
#include <vector>
using namespace std;

// 문자열의 길이는 3이상 50 이하이다.
char bowl[51];

// 그릇을 바닥에 놓았을 때 그 높이는 10cm 이다. 
// 두 개의 그릇을 같은 방향으로 포개면 그 높이는 5cm만 증가된다. 
// 입력 문자열에서 열린 괄호 ‘(’은 바로 놓인 그릇, 닫힌 괄호 ‘)’은 거꾸로 놓인 그릇을 나타난다. 
int search();

// 여러분은 그릇 방향이 괄호 문자로 표시된 문자열을 읽어서 그 최종의 높이를 정수로 출력해야 한다.
int main(){
    
    cin >> bowl;

    cout << search() << "\n";

    return 0;
}

int search(){
    enum state { UP = 0, DOWN = 1 };
    vector<int> q;

    int idx = 0;
    while(bowl[idx] != 0){
        if(bowl[idx] == '(') 
            q.push_back(UP);
        else 
            q.push_back(DOWN);
        idx++;
    }

    // 가장 처음 그릇
    int res = 10;
    int cnt = 1;

    // 이전 그릇(bowl[p])과 현재 그릇(bowl[c])을 비교
    for(int p = 0, c = 1; c < idx; p++, c++){
        if(bowl[p] != bowl[c])
            res += 10;
        else
            res += 5;
    }

    return res;
}
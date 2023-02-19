/**
 * 
 * 백준 10974번, 모든 순열
 * 191003
 * https://www.acmicpc.net/problem/10974
 * 
*/
#include <iostream>
#include <vector>
using namespace std;

// N이 주어졌을 때, 1부터 N까지의 수로 이루어진 순열을 사전순으로 출력하는 프로그램을 작성하시오.
int N;

vector<int> number;
bool check[10] = { false, };

void DFS(int cnt);

int main(){
    // 첫째 줄에 N(1 ≤ N ≤ 8)이 주어진다. 
    cin >> N;

    // 첫째 줄부터 N!개의 줄에 걸쳐서 모든 순열을 사전순으로 출력한다.
    DFS(0);
    
    return 0;
}

void DFS(int idx){
    if( idx > N ) return;

    if ( idx == N ){
        for(int i = 0 ; i < number.size(); i++){
            cout << number[i] << ' ';
        }
        cout << '\n';
    }

    for(int i = 1; i <= N; i++){
        if(check[i])    continue;
        
        check[i] = true;
        number.push_back(i);
        DFS(idx+1);
        number.pop_back();
        check[i] = false;
    }
}
/**
 * 
 * 백준 6603번, 로또
 * 190517
 * https://www.acmicpc.net/problem/6603
 * 
*/
#include <iostream>
#include <vector>
using namespace std;

// 각 테스트 케이스는 한 줄로 이루어져 있다. 첫 번째 수는 k (6 < k < 13)이다.
int K;

// 다음 k개 수는 집합 S에 포함되는 수이다. S의 원소는 오름차순으로 주어진다.
vector<int> S;

// 독일 로또는 {1, 2, ..., 49}에서 수 6개를 고른다.
// 각 테스트 케이스마다 수를 고르는 모든 방법을 출력한다. 이때, 사전 순으로 출력한다.
void DFS(int idx, int cnt);
vector<bool> check;

// 집합 S와 k가 주어졌을 때, 수를 고르는 모든 방법을 구하는 프로그램을 작성하시오.
int main(){

    // 입력은 여러 개의 테스트 케이스로 이루어져 있다. 
    do{
        cin >> K;
        // 입력의 마지막 줄에는 0이 하나 주어진다.
        if(!K) continue;

        S.clear();
        check.clear();
        for(int k = 0; k < K; k++){
            int input_;
            cin >> input_;
            S.push_back(input_);
            check.push_back(false);
        }

        
        DFS(0, 0);
        // 각 테스트 케이스 사이에는 빈 줄을 하나 출력한다.
        cout << "\n";

    } while(K);

/**
 *  
 * K가 0일 때까지 입력.
 * 
 *  while(cin >> K && K){
 *      for(int k = 0; k < K; k++){
 *          int input_;
 *          cin >> input_;
 *          S.push_back(input_);
 *      }
 *  }
 * 
*/

    return 0;
}

void DFS(int idx, int cnt){

    if(cnt == 6){
        for(int i = 0; i < S.size(); ++i){
            if(check[i])
                cout << S[i] << " ";
        }
        cout << "\n";
    }

    for(int i = idx; i < S.size(); i++){
        check[i] = true;
        DFS(i + 1, cnt + 1);
        check[i] = false;
    }
}
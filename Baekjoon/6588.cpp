/**
 * 
 * 백준 6588번, 골드바흐의 추측
 * 190524
 * https://www.acmicpc.net/problem/6588
 * 
*/
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// 각 테스트 케이스는 짝수 정수 n 하나로 이루어져 있다. (6 ≤ n ≤ 1000000)
int N;

// 4보다 큰 모든 짝수는 두 홀수 소수의 합으로 나타낼 수 있다.
// 백만 이하의 모든 짝수에 대해서, 이 추측을 검증하는 프로그램을 작성하시오.
void guess(int N);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    // 입력은 하나 또는 그 이상의 테스트 케이스로 이루어져 있다. 테스트 케이스의 개수는 100,000개를 넘지 않는다.
    // 입력의 마지막 줄에는 0이 하나 주어진다.
    while(cin >> N && N != 0)
        guess(N);

    return 0;
}
void guess(int N){
    
    vector<bool> v(N, false);
    v[0] = v[1] = true;
    for(int i = 2; i < sqrt(N); i++){
        if(v[i]) continue;

        for(int j = i * i; j < N; j += i)
            v[j] = true;
    }

    for(int i = 3; i < N/2; i += 2){
        if(!v[i]){
            if(!v[N-i]){
                // 각 테스트 케이스에 대해서, n = a + b 형태로 출력한다. 이때, a와 b는 홀수 소수이다. 
                cout << N << " = " << i << " + " << N-i << "\n";
                // 만약, n을 만들 수 있는 방법이 여러 가지라면, b-a가 가장 큰 것을 출력한다. 
                return;
            }
        }
    }
    // 또, 두 홀수 소수의 합으로 n을 나타낼 수 없는 경우에는 "Goldbach's conjecture is wrong."을 출력한다.
    cout << "Goldbach's conjecture is wrong.\n";
}
/*
#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1000000;

int minFactor[MAX];
vector<int> prime; //소수

//에라토스테네스의 체
void eratosthenes(void)
{
    minFactor[0] = minFactor[1] = -1;
    for (int i = 2; i < MAX; i++)
        minFactor[i] = i;
    for (int i = 2; i*i < MAX; i++)
        if (minFactor[i] == i)
            for (int j = i * i; j < MAX; j += i)
                if (minFactor[j] == j)
                    minFactor[j] = i;
    //홀수인 소수를 저장
    for (int i = 3; i < MAX; i++)
        if (minFactor[i] == i)
            prime.push_back(i);
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    eratosthenes();
    while (1)
    {
        int N;
        cin >> N;
        if (N == 0)
            break;
        //소수를 탐색하며
        for(int i=0; i<prime.size(); i++)
            //N - prime[i]도 소수인 수를 찾는다
            if (minFactor[N - prime[i]] == N - prime[i])
            {
                cout << N << " = " << prime[i] << " + " << N - prime[i] << "\n";
                break;
            }
    }
    return 0;
}
*/
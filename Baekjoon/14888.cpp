/**
 * 
 * 백준 14888번, 연산자 끼워넣기
 * 190927
 * https://www.acmicpc.net/problem/14888
 * 
*/
#include <iostream>
#include <limits.h>
using namespace std;

// N개의 수로 이루어진 수열 A1, A2, ..., AN이 주어진다. 
int number[12];
int N;

// 또, 수와 수 사이에 끼워넣을 수 있는 N-1개의 연산자가 주어진다. 
// 연산자는 덧셈(+), 뺄셈(-), 곱셈(×), 나눗셈(÷)으로만 이루어져 있다.
int op[4];
enum op_enum { ADD = 0, SUB, MUL, DIV, NONE };
int choose[12];

// 식의 계산은 연산자 우선 순위를 무시하고 앞에서부터 진행해야 한다. 또, 나눗셈은 정수 나눗셈으로 몫만 취한다.
int maximum = INT_MIN;
int minimum = INT_MAX;
void DFS(int idx, int op_);
int cur;

// N개의 수와 N-1개의 연산자가 주어졌을 때, 만들 수 있는 식의 결과가 최대인 것과 최소인 것을 구하는 프로그램을 작성하시오.
int main(){

    // 첫째 줄에 수의 개수 N(2 ≤ N ≤ 11)가 주어진다. 
    cin >> N;

    // 둘째 줄에는 A1, A2, ..., AN이 주어진다. (1 ≤ Ai ≤ 100) 
    for(int i = 0; i < N; i++){
        cin >> number[i];
        choose[i] = NONE;
    }
    cur = number[0];
    
    // 셋째 줄에는 합이 N-1인 4개의 정수가 주어지는데, 차례대로 덧셈(+)의 개수, 뺄셈(-)의 개수, 곱셈(×)의 개수, 나눗셈(÷)의 개수이다. 
    for(int i = 0; i < 4; i++)
        cin >> op[i];

    DFS(0, ADD);

    // 첫째 줄에 만들 수 있는 식의 결과의 최댓값을, 둘째 줄에는 최솟값을 출력한다. 
    cout << maximum << '\n';
    cout << minimum << '\n';

    return 0;
}

void DFS(int idx, int op_e){
    if(op[op_e] == 0){
        if(op_e == DIV){
            for(int i = 0; i < N-1; i++){
                switch(choose[i]){
                    case ADD:
                        cur += number[i+1];
                        break;
                    case SUB:
                        cur -= number[i+1];
                        break;
                    case MUL:
                        cur *= number[i+1];
                        break;
                    case DIV:
                        cur /= number[i+1];
                        break;
                }
            }
            maximum = max(maximum, cur);
            minimum = min(minimum, cur);
            cur = number[0];
            return;
        }
        else
            DFS(0, op_e + 1);
    }

    for(int i = idx; i < N-1; i++){
        if(choose[i] == NONE){
            choose[i] = op_e;
            op[op_e]--;

            DFS(i+1, op_e);

            choose[i] = NONE;
            op[op_e]++;
        }
    }
}
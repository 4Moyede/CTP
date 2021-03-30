/**
 * 
 * Baekjoon 10845, 큐
 * 210330
 * https://www.acmicpc.net/problem/10845
 * 
*/
#include <iostream>
using namespace std;

// 정수를 저장하는 큐를 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.
int q[100001];
int start_idx = 0;
int end_idx = 0;

// 명령은 총 여섯 가지이다.
// push X: 정수 X를 큐에 넣는 연산이다.
void push(int X);

// pop: 큐에서 가장 앞에 있는 정수를 빼고, 그 수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
int pop();

// size: 큐에 들어있는 정수의 개수를 출력한다.
int size();

// empty: 큐가 비어있으면 1, 아니면 0을 출력한다.
int empty();

// front: 큐의 가장 앞에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
int front();

// back: 큐의 가장 뒤에 있는 정수를 출력한다. 만약 큐에 들어있는 정수가 없는 경우에는 -1을 출력한다.
int back();

// 첫째 줄에 주어지는 명령의 수 N (1 ≤ N ≤ 10,000)이 주어진다.
int N;

int main(){    
    cin >> N;
    // 둘째 줄부터 N개의 줄에는 명령이 하나씩 주어진다. 주어지는 정수는 1보다 크거나 같고, 100,000보다 작거나 같다. 문제에 나와있지 않은 명령이 주어지는 경우는 없다.
    for(int n = 0; n < N; n++){
        string command;
        int number;
        cin >> command;
        
        // 출력해야하는 명령이 주어질 때마다, 한 줄에 하나씩 출력한다.
        if(command == "push"){
            cin >> number;
            push(number);
        }
        else if(command == "pop")   cout << pop() << '\n';
        else if(command == "size")  cout << size() << '\n';
        else if(command == "empty") cout << empty() << '\n';
        else if(command == "front") cout << front() << '\n';
        else if(command == "back")  cout << back() << '\n';
    }

    return 0;
}

void push(int X){
    q[end_idx++] = X;
}

int pop(){
    if(empty()) return -1;
    else        return q[start_idx++];
}

int size(){
    return end_idx - start_idx;
}

int empty(){
    if(size())  return 0;
    else        return 1;
}

int front(){
    if(empty()) return -1;
    else        return q[start_idx];
}

int back(){
    if(empty()) return -1;
    else        return q[end_idx-1];
}

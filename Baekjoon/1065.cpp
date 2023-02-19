/**
 * 
 *  백준 1065번, 한수
 *  191015
 *  https://www.acmicpc.net/problem/1065
 * 
*/
#include <iostream>
using namespace std;

// N이 주어졌을 때, 1보다 크거나 같고, N보다 작거나 같은 한수의 개수를 출력하는 프로그램을 작성하시오. 
int N;
int cnt = 99;

void solve();

int main(){
    // 첫째 줄에 1,000보다 작거나 같은 자연수 N이 주어진다.
    cin >> N;

    // 첫째 줄에 1보다 크거나 같고, N보다 작거나 같은 한수의 개수를 출력한다.
    if(N < 100){
        cout << N << '\n';
    }
    else{
        solve();
        cout << cnt << '\n';
    }
}

void solve(){
    // 어떤 양의 정수 X의 자리수가 등차수열을 이룬다면, 그 수를 한수라고 한다.
    int cur = 100;
    while( cur <= N ){
        int check = cur;
 
        int one = check % 10;
        check /= 10;
        int two = check % 10;
        check /= 10;
        int add = one - two;

        bool one_num = true;
        while(check){
            one = two;
            two = check % 10;
            check /= 10;
            if(one - two != add){
                one_num = false;
                break;
            }
        }

        if(one_num)
            cnt++;
        cur++;
    }
}
/**
 * 
 *  백준 1759번, 암호 만들기
 *  191210
 *  https://www.acmicpc.net/problem/1759
 * 
*/
#include <iostream>
#include <algorithm>
using namespace std;

// 암호는 서로 다른 L개의 알파벳 소문자들로 구성되며 
int L;

// 최소 한 개의 모음과 최소 두 개의 자음으로 구성되어 있다고 알려져 있다. 
int vowels_cnt = 0;
int consonants_cnt = 0;

// 암호를 이루는 알파벳이 암호에서 증가하는 순서로 배열되었다.
// C개의 문자들이 모두 주어졌을 때, 가능성 있는 암호들을 모두 구하는 프로그램을 작성하시오.
int C;
char alpha[16];
bool check[16] = { false, };

void DFS(int idx, int cnt);
void before(char c, int idx);
void after(char c, int idx);

int main(){

    // 첫째 줄에 두 정수 L, C가 주어진다. (3 ≤ L ≤ C ≤ 15) 
    cin >> L >> C;

    // 다음 줄에는 C개의 문자들이 공백으로 구분되어 주어진다. 주어지는 문자들은 알파벳 소문자이며, 중복되는 것은 없다.
    for(int i = 0; i < C; i++)
        cin >> alpha[i];

    // 각 줄에 하나씩, 사전식으로 가능성 있는 암호를 모두 출력한다.
    sort(alpha, alpha + C);
    DFS(0, 0);

    return 0;
}

void DFS(int idx, int cnt){

    if(cnt == L){
        if(vowels_cnt >= 1 && consonants_cnt >= 2){
            for(int i = 0; i < C; i++)
                if(check[i])
                    cout << alpha[i];
            cout << '\n';
        }

        return;
    }

    for(int i = idx; i < C; i++){
        if(!check[i]){
            before(alpha[i], i);
            DFS(i, cnt + 1);
            after(alpha[i], i);
        }
    }
}


void before(char c, int idx){
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        vowels_cnt++;
    else 
        consonants_cnt++;
    check[idx] = true;
}

void after(char c, int idx){
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        vowels_cnt--;
    else 
        consonants_cnt--;
    check[idx] = false;
}
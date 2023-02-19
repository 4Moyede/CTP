/**
 * 
 * 백준 2529번, 부등호
 * 190930
 * https://www.acmicpc.net/problem/2529
 * 
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

// 두 종류의 부등호 기호 ‘<’와 ‘>’가 k개 나열된 순서열  A가 있다.
char A[10]; 
int K;

vector<int> v;
bool check[10] = { 0, };

// 우리는 이 부등호 기호 앞뒤에 서로 다른 한 자릿수 숫자를 넣어서 모든 부등호 관계를 만족시키려고 한다.
// 부등호 기호 앞뒤에 넣을 수 있는 숫자는 0부터 9까지의 정수이며 선택된 숫자는 모두 달라야 한다.
void DFS(int cnt);

bool correct(vector<int> num);
long vec_num(vector<int> v);

// 부등호 기호를 제거한 뒤, 숫자를 모두 붙이면 하나의 수를 만들 수 있는데 이 수를 주어진 부등호 관계를 만족시키는 정수라고 한다. 
// 제시된 k개의 부등호 순서를 만족하는 (k+1)자리의 정수 중에서 최댓값과 최솟값을 찾아야 한다. 
long max_number = LONG_MIN;
vector<int> max_vector;
long min_number = LONG_MAX;
vector<int> min_vector;

int main(){
    // 첫 줄에 부등호 문자의 개수를 나타내는 정수 k가 주어진다. 그 다음 줄에는 k개의 부등호 기호가 하나의 공백을 두고 한 줄에 모두 제시된다. k의 범위는 2 ≤ k ≤ 9 이다. 
    cin >> K;
    for(int k = 0; k < K; k++)
        cin >> A[k];

    DFS(0);

    // 제시된 부등호 관계를 만족하는 k+1 자리의 최대, 최소 정수를 첫째 줄과 둘째 줄에 각각 출력해야 한다.
    for(int i = 0 ; i < max_vector.size(); i++){
        cout << max_vector[i];
    }
    cout << '\n';
    for(int i = 0 ; i < min_vector.size(); i++){
        cout << min_vector[i];
    }
    cout << '\n';

    return 0;
}

void DFS(int cnt){
    if(cnt > K+1)   return;

    if(cnt == K+1){
        if(correct(v)){
            long inequal_num = vec_num(v);
            if(max_number < inequal_num){
                max_number = inequal_num;
                max_vector.clear();
                int cnt = max_vector.size();
                for(int c = 0; c < cnt; c++){
                    max_vector.push_back(0);
                }
                for(int c = 0; c < v.size(); c++){
                    max_vector.push_back(v[c]);
                }
            }
            if(min_number > inequal_num){
                min_number = inequal_num;
                min_vector.clear();
                int cnt = min_vector.size() - (K+1);
                for(int c = 0; c < cnt; c++){
                    min_vector.push_back(0);
                }
                for(int c = 0; c < v.size(); c++){
                    min_vector.push_back(v[c]);
                }
            }
        }
    }

    for(int i = 0 ; i < 10; i++){
        if(check[i])    continue;

        check[i] = true;
        v.push_back(i);
        DFS(cnt+1);
        v.pop_back();
        check[i] = false;
    }
}

bool correct(vector<int> num){
    bool ans = true;

    int k = 0;
    while(ans){

        if(count(num.begin(), num.end(), num[k]) > 1){
            ans = false;
            continue;
        }

        if(A[k] == '<'){
            if(num[k] >= num[k+1]){
                ans = false;
                continue;
            }
        }
        else{
            if(num[k] <= num[k+1]){
                ans = false;
                continue;
            }
        }

        k++;
        if(k == K)
            break;
    }

    return ans;
}

long vec_num(vector<int> v){

    long num = v[0];
    for(int i = 1; i < v.size(); i++){
        num *= 10;
        num += v[i];
    }

    return num;
}
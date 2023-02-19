/**
 * 
 * 백준 1107번, 리모컨
 * 190102
 * https://www.acmicpc.net/problem/1107
 * 
*/
#include <iostream>
#include <vector>
#include <algorithm>

#define CURRENT 100

using namespace std;

int number[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int result[3] = {0, 0, 0};

bool possible(int num, int &digit)
{
	digit = 0;
	vector<int> channel;
	int temp = num;
	
	do
	{
		int n = temp % 10;
		temp /= 10;
		channel.push_back(n);
		digit++;
	} while(temp);
	reverse(channel.begin(), channel.end());

	for(int i = 0; i < digit; i++)
		if(!number[channel[i]])
			return false;
	
	return true;
}

int getNearest(int want, int cal)
{
	bool find = false;
	int start = want;
	int digit = 0;
	while(!find && start >= 0)
	{
		find = possible(start, digit);
		if(!find)
			start += cal;
		if(start < 0)
			return -1;
		if(cal == 1 && abs(start - want) + digit > result[0])
			return -1;
		if(cal == -1 && abs(start - want) + digit > result[0] && abs(start - want) + digit > result[1])
			if(result[1] != -1)
				return -1;
	}
	return abs(start - want) + digit;
}

int main()
{
	int want;
	int unusable;
	
	cin >> want >> unusable;
	for(int i = 0; i < unusable; i++)
	{
		int input;
		cin >> input;
		number[input]--;
	}
	result[0] = abs(want - CURRENT);
	result[1] = getNearest(want, 1);
	result[2] = getNearest(want, -1);

	sort(result, result+3);
	for(int i = 0; i < 3; i++)
		if(result[i] != -1)
		{
			cout << result[i] << "\n";
			return 0;
		}
	return 0;
}

/**
 * 
 * 백준 6064번, 카잉 달력
 * 190116
 * https://www.acmicpc.net/problem/6064
 * 
*/
#include <iostream>
using namespace std;

long cal(long numeralSys, long cur, long rule);
long lcm(long a, long b);

int main()
{
	int test;
	long N, M, x, y;

	cin >> test;
	for(int i = 0; i < test; i++)
	{
		cin >> N >> M >> x >> y;

		if(N > M)
		{
			int temp = N;
			N = M;
			M = temp;
			temp = x;
			x = y;
			y = temp;
		}
		long rule = N - M;
		long cur = x;
		long year = x;
		bool find = false;
		long loop = lcm(N, M) / N;

		for(long j = 0; j <= loop; j++)
		{
			if(y == cur)
			{
				find = true;
				break;
			}

			cur = cal(M, cur, rule);
			year += N;
		}

		if(!find)
			year = -1;

		cout << year << "\n";
	}

	return 0;
}

long cal(long numeralSys, long cur, long rule)
{
	long result = cur + rule;

	if(result <= 0)
	{
		while(result <= 0)
			result += numeralSys;
	}
	else if(result > numeralSys)
	{
		while(result > numeralSys)
			result -= numeralSys;
	}
	
	return result;
}
long lcm(long a, long b)
{
	long pa = a, pb = b;

	long c;
	while(b != 0)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return pa * pb / a; 
}


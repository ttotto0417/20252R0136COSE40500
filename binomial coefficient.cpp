// https://www.acmicpc.net/problem/13977 binomial coefficient

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

long long dncPower(const long long a, const long long b, const long long p); // a^b % p

long long factorial[4000001];

int main(void)
{
	int m;
	scanf("%d", &m);

	const long long p = 1000000007;

	//memoization of factorials
	
	factorial[0] = 1;

	long long temp = 1;
	for (int i = 1; i < 4000001; i++) {
		temp = (temp * i) % p;
		factorial[i] = temp;
	}

	for (int testNum = 0; testNum < m; testNum++) {

		long long n, k;
		scanf("%lld %lld", &n, &k);		

		// n! / k!(n-k)! \equiv n! * ( (n-k)!k! )^(p-2) (mod p) fermat's thm

		// calculate (n-k)! k!
		long long result = ( factorial[n - k] * factorial[k] ) % p;

		// calculate ( (n-k)!k! )^(p-2) mod p
		
		result = dncPower(result, p - 2, p);

		result = (factorial[n] * result) % p;

		printf("%lld\n", result);
	}

	return 0;
}

long long dncPower(const long long a, const long long b, const long long p)
{
	if (b == 1) return a % p;
	else {
		long long half = dncPower(a, b / 2, p);
		if (b % 2 == 0) {
			return (half * half) % p;
		}
		else {
			return (((a * half) % p) * half) % p;
		}
	}
}
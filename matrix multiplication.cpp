// https://www.acmicpc.net/problem/11049 maxtix multiplication
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

using namespace std;

long long DP[501][501] = {0,}; // DP[i][j] is min no. of multiplications for matrices i - j
int r[501], c[501]; // row, col
int maxLong = 2147483647;

// DP[i][j] = min(k = i ~ j - 1 | DP[i][k] + DP[k+1][j] + r[i] * c[k] * c[j])

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i < n + 1; i++) {
		scanf("%d %d", &r[i], &c[i]);
	}

	for (int i = 1; i < n; i++) { // number of matrices to be multiplicated
		for (int j = 1; j < n - i + 1; j++) { // starting index

			DP[j][i + j] = maxLong;
			for (int k = j; k < i + j; k++) {
				DP[j][i + j] = min(DP[j][i + j], DP[j][k] + DP[k + 1][i + j]
				+ r[j] * c[k] * c[i + j]);
			}
		}
	}
	/*
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			printf("DP[%d][%d] = %lld\n", i, j, DP[i][j]);
		}
	} */

	printf("%lld\n", DP[1][n]);
	
	return 0;
}

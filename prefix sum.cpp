// https://www.acmicpc.net/problem/11660 prefix sum
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int table[1025][1025] = { 0, };
int DP[1025][1025] = { 0, }; // DP[i][j] := sum from (1,1) to (i,j)

int findSum(int x1, int y1, int x2, int y2);

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int row = 1; row <= n; row++) {
		for (int col = 1; col <= n; col++) {
			scanf("%d", &table[row][col]);
			
			DP[row][col] = table[row][col] + DP[row - 1][col] + DP[row][col - 1]
				- DP[row - 1][col - 1];
		}
	}

	int x1, y1, x2, y2;

	for (int testnum = 0; testnum < m; testnum++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		printf("%d\n", findSum(x1, y1, x2, y2));
	}

	return 0;
}

int findSum(int x1, int y1, int x2, int y2)
{
	return DP[x2][y2] - DP[x1 - 1][y2] - DP[x2][y1 - 1] + DP[x1 - 1][y1 - 1];
}
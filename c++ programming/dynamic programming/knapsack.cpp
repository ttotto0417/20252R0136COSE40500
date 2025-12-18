//https://www.acmicpc.net/problem/7579 knapsack
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

using namespace std;

int DP[101][10001] = { 0, }; // DP[i][j] is max. bytes using a_1 - a_i, using cost j
int memory[101], cost[101];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i < n + 1; i++) {
		scanf("%d", &memory[i]);
	}

	int sumCost = 0;

	for (int i = 1; i < n + 1; i++) {
		scanf("%d", &cost[i]);
		sumCost += cost[i];
	}

	for (int i = 1; i < n + 1; i++) {
		for (int j = 0; j < sumCost + 1; j++) {
			if (j >= cost[i]) {
				DP[i][j] = max(DP[i - 1][j], DP[i - 1][j - cost[i]] + memory[i]);
			}
			DP[i][j] = max(DP[i][j], DP[i - 1][j]);
		}
	}

	for (int i = 0; i < sumCost + 1; i++) {
		if (DP[n][i] >= m) {
			printf("%d", i);
			break;
		}
	}

	return 0;
}

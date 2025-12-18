// https://www.acmicpc.net/problem/11404 floyd-warshall
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>


int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	int maxInt = 1047483647;

	int** graph = (int**)malloc(sizeof(int*) * (n + 1));
	if (graph == NULL) return -1;

	for (int i = 0; i < n + 1; i++) {
		graph[i] = (int*)malloc(sizeof(int) * (n + 1));
		if (graph[i] == NULL) return -1;

		for (int j = 0; j < n + 1; j++) {
			graph[i][j] = (i == j) ? 0 : maxInt;
		}
	}

	int a, b, c;

	for (int edgeNum = 0; edgeNum < m; edgeNum++) {
		scanf("%d %d %d", &a, &b, &c);

		if (c < graph[a][b]) graph[a][b] = c;
	}

	int** minDist = (int**)malloc(sizeof(int*) * (n + 1));
	if (minDist == NULL) return -1;

	for (int i = 0; i < n + 1; i++) {
		minDist[i] = (int*)malloc(sizeof(int) * (n + 1));
		if (minDist[i] == NULL) return -1;

		for (int j = 0; j < n + 1; j++) {
			minDist[i][j] = graph[i][j];
		}
	}

	// floyd-warshall
	for (int numNode = 1; numNode < n + 1; numNode++) {
		for (int sNode = 1; sNode < n + 1; sNode++) {
			for (int tNode = 1; tNode < n + 1; tNode++) {
				if (minDist[sNode][numNode] + minDist[numNode][tNode] < minDist[sNode][tNode]) {
					minDist[sNode][tNode] = minDist[sNode][numNode] + minDist[numNode][tNode];
				}
			}
		}
	}

	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			printf("%d ", (minDist[i][j] == maxInt) ? 0 : minDist[i][j]);
		}
		printf("\n");
	}

	return 0;
}
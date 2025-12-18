// shortest path faster algorithm, negative cycle detection
// https://www.acmicpc.net/problem/11657
// why so slow?

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstring>


int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	int maxInt = 2147483647;

	int** graph = (int**)malloc(sizeof(int*) * (n + 1));
	if (graph == NULL) return -1;

	for (int i = 0; i < n + 1; i++) {
		graph[i] = (int*)malloc(sizeof(int) * (n + 1));
		if (graph[i] == NULL) return -1;

		for (int j = 0; j < n + 1; j++) { // initialize as maxInt
			graph[i][j] = maxInt;
		}
	}

	int sNode, tNode, edgeTime;
	for (int edgeNum = 0; edgeNum < m; edgeNum++) {
		scanf("%d %d %d", &sNode, &tNode, &edgeTime);

		if (edgeTime < graph[sNode][tNode]) {
			graph[sNode][tNode] = edgeTime;
		}
	}

	// minimum dist to each node
	long* minDist = (long*)malloc(sizeof(long) * (n + 1));
	if (minDist == NULL) return -1;

	for (int i = 0; i < n + 1; i++) {
		minDist[i] = maxInt;
	}

	// number of visits to each node, for negative cycle detection
	int* numVisit = (int*)malloc(sizeof(int) * (n + 1));
	if (numVisit == NULL) return -1;

	memset(numVisit, 0, sizeof(int) * (n + 1));

	int s = 1; // start node
	minDist[s] = 0;

	std::queue<int> searchQueue; // queue for spfa

	searchQueue.push(s);

	int currNode;
	int negCycle = 0; // 1 if negative cycle exists

	int* inQueue = (int*)malloc(sizeof(int) * (n + 1));
	if (inQueue == NULL) return -1;

	memset(inQueue, 0, sizeof(int) * (n + 1));

	inQueue[s] = 1;

	long currDist;

	while (!searchQueue.empty()) {
		currNode = searchQueue.front();
		searchQueue.pop();
		inQueue[currNode] = 0;

		//printf("currNode is %d\n", currNode);

		++numVisit[currNode];

		if (numVisit[currNode] >= n) { // any path must contain <= |V| - 1 edges, or negcycle
			//printf("negative cycle\n");
			negCycle = 1;
			break;
		}

		// for each edge (currnode, v)
		for (int nodeNum = 1; nodeNum < n + 1; nodeNum++) {
			currDist = graph[currNode][nodeNum];
			if (currDist == maxInt) continue;

			//printf("current adjacent node is %d\n", nodeNum);

			if (minDist[currNode] + currDist < minDist[nodeNum]) { // new shortest dist
				/*printf("minDist[%d] + %d  = %ld < minDist[%d] = %ld\n", currNode, currDist, minDist[currNode] + currDist,
					nodeNum, minDist[nodeNum]); */
				minDist[nodeNum] = minDist[currNode] + currDist;

				if (!inQueue[nodeNum]) {
					//printf("%d not in queue, pushed\n", nodeNum);
					searchQueue.push(nodeNum);
				}
			}
		}

	}

	if (negCycle) {
		printf("-1\n");
		return 0;
	}

	for (int nodeNum = s + 1; nodeNum < n + 1; nodeNum++) {
		if (minDist[nodeNum] == (long)maxInt) {
			printf("-1\n");
		}
		else {
			printf("%ld\n", minDist[nodeNum]);
		}
	}

	return 0;
}
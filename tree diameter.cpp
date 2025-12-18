// https://www.acmicpc.net/problem/1167 tree diameter
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

// tree[u] contains <v, d(u, v)>'s
array<vector<pair<int, int>>, 100001> tree;
array<int, 100001> visited = { 0, };
array<long long, 100001> minDist;
queue<int> dfsQueue;

int main(void)
{
	int v;
	scanf("%d", &v);

	pair<int, int> currPair;
	int currNode;
	int AdjNode;
	int edgeDist;

	for (int i = 0; i < v; i++) {
		scanf("%d", &currNode);
		while (1) {
			scanf("%d", &AdjNode);
			if (AdjNode == -1) break;
			else {
				scanf("%d", &edgeDist);
				currPair.first = AdjNode;
				currPair.second = edgeDist;
				tree[currNode].push_back(currPair);
			}
		}
	}

	long long maxLong = 2147483647;
	minDist[1] = 0;

	for (int i = 2; i <= v; i++) {
		minDist[i] = maxLong;
	}

	long long currDist;
	long long maxDist = 0;
	int farNode = 1;

	dfsQueue.push(1);

	while (!dfsQueue.empty()) {
		currNode = dfsQueue.front();
		dfsQueue.pop();
		visited[currNode] = 1;
		currDist = minDist[currNode];
		for (int j = 0; j < tree[currNode].size(); j++) {
			AdjNode = tree[currNode][j].first;
			edgeDist = tree[currNode][j].second;
			if (!visited[AdjNode]) {
				dfsQueue.push(AdjNode);
				minDist[AdjNode] = currDist + edgeDist;
				if (minDist[AdjNode] > maxDist) {
					maxDist = minDist[AdjNode];
					farNode = AdjNode;
				}
			}
		}
	}

	//printf("farNode is %d, maxDist is %lld\n", farNode, maxDist);

	for (int i = 1; i <= v; i++) {
		if (i == farNode) minDist[i] = 0;
		else minDist[i] = maxLong;
	}

	dfsQueue.push(farNode);
	maxDist = 0;
	visited = { 0, };

	while (!dfsQueue.empty()) {
		currNode = dfsQueue.front();
		dfsQueue.pop();
		visited[currNode] = 1;
		currDist = minDist[currNode];
		for (int j = 0; j < tree[currNode].size(); j++) {
			AdjNode = tree[currNode][j].first;
			edgeDist = tree[currNode][j].second;
			if (!visited[AdjNode]) {
				dfsQueue.push(AdjNode);
				minDist[AdjNode] = currDist + edgeDist;
				if (minDist[AdjNode] > maxDist) {
					maxDist = minDist[AdjNode];
					farNode = AdjNode;
				}
			}
		}
	}

	//printf("farNode is %d, maxDist is %lld\n", farNode, maxDist);

	printf("%lld\n", maxDist);

	return 0;
}
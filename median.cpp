// https://www.acmicpc.net/problem/1655 continuously finding median using two priority queues
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main(void)
{
	int n;
	scanf("%d", &n);

	int currNum;

	priority_queue<int> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;

	int median = 10001;

	int moveNum;

	for (int i = 0; i < n; i++) {
		scanf("%d", &currNum);

		//printf("median is %d\n", median);

		if (currNum > median) {
			minHeap.push(currNum);
			//printf("pushed to minHeap\n");
		}
		else {
			maxHeap.push(currNum);
			//printf("pushed to maxHeap\n");
		}

		if (minHeap.size() > maxHeap.size()) {
			
			moveNum = minHeap.top();
			minHeap.pop();
			maxHeap.push(moveNum);
			//printf("minHeap too large, moved %d to maxHeap\n", moveNum);
		}

		if (maxHeap.size() > minHeap.size() + 1) {
			moveNum = maxHeap.top();
			maxHeap.pop();
			minHeap.push(moveNum);
			//printf("maxHeap too large, moved %d to minHeap\n", moveNum);
		}

		median = maxHeap.top();
		printf("%d\n", median);
	}


	return 0;
}

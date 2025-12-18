// https://www.acmicpc.net/problem/14003 longest increasing subsequence with indexing
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

int main(void)
{
	int n; // length of array
	scanf("%d", &n);

	int* targetArray = (int*)malloc(sizeof(int) * n); // stores input array
	if (targetArray == NULL) return -1;

	for (int i = 0; i < n; i++) {
		scanf("%d", &targetArray[i]);
	}

	int* indexArray = (int*)malloc(sizeof(int) * n); // stores index of A[i] in LIS
	if (indexArray == NULL) return -1;

	std::vector<int> LIS; // longest increasing subsequence

	LIS.push_back(targetArray[0]);
	indexArray[0] = 0;

	int currNum;
	int lbIndex; // lower bound index

	for (int elementNum = 1; elementNum < n; elementNum++) {
		currNum = targetArray[elementNum];
		if (currNum > LIS.back()) { // current number is greater, just push
			LIS.push_back(currNum);
			indexArray[elementNum] = (int)LIS.size() - 1;
		}
		else { // find the lower bound in LIS by binary search
			lbIndex = (int)std::distance(LIS.begin(), std::lower_bound(LIS.begin(), LIS.end(), currNum));
			LIS[lbIndex] = currNum;
			indexArray[elementNum] = lbIndex;
		}
	}

	int lisSize = (int)LIS.size();
	printf("%d\n", lisSize);
	
	std::stack<int> finalLIS;

	// starting from the rear, find elements in exact LIS
	for (int i = n - 1; i >= 0; i--) {
		if (indexArray[i] == lisSize - 1) {
			finalLIS.push(targetArray[i]);
			lisSize--;
		}
		
	}

	while (!finalLIS.empty()) {
		printf("%d ", finalLIS.top());
		finalLIS.pop();
	}
	
	return 0;
}

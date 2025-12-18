// https://www.acmicpc.net/problem/3015 stack application
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>

using namespace std;

int main(void)
{
	int n;
	scanf("%d", &n);

	stack<pair<int, long long>> line;

	long long count = 0;

	pair<int, long long> currPair, topPair;

	int currHeight;

	for (int i = 0; i < n; i++) {
		scanf("%d", &currHeight);
		
		currPair.first = currHeight;
		currPair.second = 1; // number of same height

		// pop all less or equal heights
		while (!line.empty() && line.top().first <= currHeight) {

			topPair = line.top();

			if (topPair.first == currHeight) {
				currPair.second = topPair.second + 1;
			}
			
			count += topPair.second;

			line.pop();
		}

		if (!line.empty()) count++;
		
		line.push(currPair);
	}

	printf("%lld\n", count);

	return 0;
}

// https://www.acmicpc.net/problem/16496 concatenate numbers to make largest
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(string a, string b);

int main(void)
{
	int n;
	scanf("%d", &n);

	vector<string> numberStrings;

	string currNum;

	bool notZero = 0;
	string zero = "0";

	for (int i = 0; i < n; i++) {
		cin >> currNum;
		numberStrings.push_back(currNum);
		if (currNum != zero) notZero = 1;
	}

	sort(numberStrings.begin(), numberStrings.end(), compare);

	if (notZero == 0) {
		printf("0\n");
		return 0;
	}

	for (int i = 0; i < n; i++) {
		cout << numberStrings[i];
	}

	puts("");

	return 0;
}

bool compare(string a, string b)
{
	string ab = a + b;
	string ba = b + a;
	
	return ab > ba;
}

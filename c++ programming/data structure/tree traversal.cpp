//https://www.acmicpc.net/problem/2263 find preorder from inorder and postorder, need to find index faster
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef vector<int> tree;

void findPre(const int begin, const int end);
int findIndex(const int treeSize, const int root);

int postIndex;
stack<int> pre;
tree in, post;

int main(void)
{
	int n;
	scanf("%d", &n);

	postIndex = n - 1;

	int temp;

	for (int i = 0; i < n; i++) {
		scanf("%d", &temp);
		in.push_back(temp);
	}

	for (int i = 0; i < n; i++) {
		scanf("%d", &temp);
		post.push_back(temp);
	}

	findPre(0, n - 1);

	while (!pre.empty()) {
		temp = pre.top();
		printf("%d ", temp);
		pre.pop();
	}

	return 0;
}

void findPre(const int begin, const int end)
{
	if (begin > end) return;
	int root = post[postIndex];
	postIndex--;

	int rootIndex = findIndex((int)in.size(), root);

	findPre(rootIndex + 1, end);
	findPre(begin, rootIndex - 1);
	pre.push(root);

	return;
}

int findIndex(const int treeSize, const int root)
{
	for (int index = 0; index < treeSize; index++) {
		if (in[index] == root)
			return index;
	}
	return -1;
}

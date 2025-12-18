// https://www.acmicpc.net/problem/1520 downhill
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> cell;
typedef vector<vector<int>> map;

void displayMap(const map& targetMap, int m, int n);
bool isInsideMap(const map& Map, int m, int n, int nextRow, int nextCol);
int dfs(const map& Map, map& DP, int m, int n, int targetRow, int targetCol);

// up down left right
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

int main(void)
{
	int m, n;

	scanf("%d %d", &m, &n);

	map Map;
	map DP; // DP[i][j] = k <=> from cell (i, j) to cell (m - 1, n - 1) there are k paths

	int temp;

	for (int row = 0; row < m; row++) {
		vector<int> currRow;
		vector<int> DPRow;
		for (int col = 0; col < n; col++) {
			scanf("%d", &temp);
			currRow.push_back(temp);
			DPRow.push_back(-1); // -1 if unvisited
		}
		Map.push_back(currRow);
		DP.push_back(DPRow);
	}

	dfs(Map, DP, m, n, 0, 0);

	//displayMap(Map, m, n);
	//displayMap(DP, m, n);

	printf("%d\n", DP[0][0] == -1 ? 0 : DP[0][0]);

	return 0;
}

void displayMap(const map& targetMap, int m, int n)
{
	for (int row = 0; row < m; row++) {
		for (int col = 0; col < n; col++) {
			printf("%d ", targetMap[row][col]);
		}
		puts("");
	}

	return;
}

bool isInsideMap(const map& Map, int m, int n, int nextRow, int nextCol)
{
	if (nextRow < 0 || nextRow >= m) return 0;
	if (nextCol < 0 || nextCol >= n) return 0;

	return 1;
}

int dfs(const map& Map, map& DP, int m, int n, int targetRow, int targetCol)
{
	if (DP[targetRow][targetCol] != -1) return DP[targetRow][targetCol];
	if (targetRow == m - 1 && targetCol == n - 1) return 1;

	DP[targetRow][targetCol] = 0;

	int nextRow, nextCol;

	for (int dir = 0; dir < 4; dir++) {
		nextRow = targetRow + dy[dir];
		nextCol = targetCol + dx[dir];
		if (isInsideMap(Map, m, n, nextRow, nextCol)) {
			if (Map[targetRow][targetCol] > Map[nextRow][nextCol]) {
				if (DP[nextRow][nextCol] != -1) DP[targetRow][targetCol] += DP[nextRow][nextCol];
				else DP[targetRow][targetCol] += dfs(Map, DP, m, n, nextRow, nextCol);
			}
		}
	}

	return DP[targetRow][targetCol];
}

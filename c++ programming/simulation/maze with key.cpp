// https://www.acmicpc.net/problem/1194 bfs with bitmasking
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

typedef pair<int, int> cell;
typedef pair<cell, cell> cellWithKeyTime;

int numRows, numCols;
char maze[50][50];
vector<bool[50][50]> visited(64);

void displayMaze(void);
void displayVisited(int keyState);
bool isInsideMaze(int row, int col);
bool isExit(int row, int col);
void cryForTheMoon(int time);
bool canMoveTo(int row, int col, int keyState);

// up down left right
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

int main(void)
{
	scanf("%d %d", &numRows, &numCols);
	getchar();

	cell startPos;

	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			scanf("%c", &maze[row][col]);
			if (maze[row][col] == '0') {
				startPos.first = row;
				startPos.second = col;
			}
		}
		getchar();
	}

	/*
	displayMaze();

	for (int i = 0; i < 64; i++) {
		displayVisited(i);
	}
	*/

	int startKeyState = 0; // 6bit integer, 010001 means has key b and f
	int startTime = 0;

	cell startKeyTime;
	startKeyTime.first = startKeyState;
	startKeyTime.second = startTime;

	queue<cellWithKeyTime> bfsQueue;

	cellWithKeyTime startCellWithKeystate;
	startCellWithKeystate.first = startPos;
	startCellWithKeystate.second = startKeyTime;

	bfsQueue.push(startCellWithKeystate);

	cellWithKeyTime currCellWithKeyTime, nextCellWithKeyTime;
	cell currCell, nextCell;
	cell currKeyTime, nextKeyTime;

	char currChar, nextChar;

	int currKeystate, nextKeystate;

	visited[0][startPos.first][startPos.second] = 1;

	while (!bfsQueue.empty()) {
		currCellWithKeyTime = bfsQueue.front();
		bfsQueue.pop();

		currCell = currCellWithKeyTime.first;
		currKeyTime = currCellWithKeyTime.second;
		currKeystate = currKeyTime.first;
		
		currChar = maze[currCell.first][currCell.second];

		/*
		printf("current cell is at row %d, col %d\n", currCell.first, currCell.second);
		printf("current key state is %d, time is %d\n", currKeystate, currKeyTime.second);
		printf("current char is %c\n", currChar);
		*/

		//printf("bfsQueue has %lld elements\n", (long long)bfsQueue.size());

		// if exit return
		if (currChar == '1') {
			cryForTheMoon(currKeyTime.second);
			
			return 0;
		}

		

		// update visited
		// visited[currKeyTime.first][currCell.first][currCell.second] = 1;

		for (int dir = 0; dir < 4; dir++) {
			nextCell.first = currCell.first + dy[dir];
			nextCell.second = currCell.second + dx[dir];

			nextKeyTime.first = currKeystate;
			nextKeyTime.second = currKeyTime.second + 1;

			if (isInsideMaze(nextCell.first, nextCell.second)) {
				if (canMoveTo(nextCell.first, nextCell.second, currKeystate) &&
					!visited[currKeystate][nextCell.first][nextCell.second]) {

					// update keystate
					nextChar = maze[nextCell.first][nextCell.second];
					if (nextChar >= 'a' && nextChar <= 'f') {
						int n = 'f' - nextChar;

						nextKeystate = currKeystate | (int)pow(2, n);
						nextKeyTime.first = nextKeystate;
					}

					nextCellWithKeyTime.first = nextCell;
					nextCellWithKeyTime.second = nextKeyTime;

					bfsQueue.push(nextCellWithKeyTime);

					/*
					printf("pushed (row %d, col %d), (keystate %d, time %d) to queue\n",
						nextCell.first, nextCell.second, nextKeyTime.first, nextKeyTime.second);
					*/

					visited[currKeystate][nextCell.first][nextCell.second] = 1;
				}
			}
		}

	}

	printf("-1\n");

	return 0;
}

void displayMaze(void)
{
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			printf("%c", maze[row][col]);
		}
		puts("");
	}

	return;
}

void displayVisited(int keyState)
{
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			printf("%d", visited[keyState][row][col]);
		}
		puts("");
	}

	return;
}

bool isExit(int row, int col)
{
	return (maze[row][col] == 1);
}

bool isInsideMaze(int row, int col)
{
	if (row < 0 || col < 0) return 0;

	if (row >= numRows || col >= numCols) return 0;

	return 1;
}

void cryForTheMoon(int time)
{
	printf("%d\n", time);

	return;
}

bool canMoveTo(int row, int col, int keyState)
{
	char targetChar = maze[row][col];

	if (targetChar == '#') return 0;

	if (targetChar >= 'A' && targetChar <= 'F') {
		int n = 'F' - targetChar;

		if ((keyState >> n) % 2 == 0) return 0;
	}

	return 1;
}

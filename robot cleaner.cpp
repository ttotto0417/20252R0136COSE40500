// https://www.acmicpc.net/problem/14503 robot cleaner
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> cell;
typedef vector<vector<int>> room;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

typedef struct robot {
	cell position;
	int direction = -1;
} Robot;

void getInput(int& numRows, int& numCols, room& initialRoom, cell& initialCell, int& initialDir);
void disPlayRoom(const int numRows, const int numCols, const room& initialRoom);
void disPlayRobot(const Robot& targetRobot);
void rotateCcw(Robot& targetRobot);
void moveF(Robot& targetRobot);
void moveB(Robot& targetRobot);
void clean(const Robot& targetRobot, room& targetRoom);
int isCleaned(const Robot& targetRobot, const room& targetRoom);
int isAdjEmpty(const Robot& targetRobot, const int numRows, const int numCols, const room& targetRoom);
int isRearClear(const Robot& targetRobot, const room& targetRoom);
int isForwardClear(const Robot& targetRobot, const room& targetRoom);
int countCleaned(const int numRows, const int numCols, const room& targetRoom);

int main(void)
{
	int numRows, numCols;	
	cell initialCell;
	int initialDir;
	room initialRoom;

	getInput(numRows, numCols, initialRoom, initialCell, initialDir);
	
	//disPlayRoom(numRows, numCols, initialRoom);

	Robot cleanRobot;
	cleanRobot.position = initialCell;
	cleanRobot.direction = initialDir;

	//disPlayRobot(cleanRobot);

	while (1) {
		if (!isCleaned(cleanRobot, initialRoom)) {
			clean(cleanRobot, initialRoom);
		}
		if (!isAdjEmpty(cleanRobot, numRows, numCols, initialRoom)) {
			if (isRearClear(cleanRobot, initialRoom)) {
				moveB(cleanRobot);
				continue;
			}
			else break;
		}
		else {
			rotateCcw(cleanRobot);
			if (isForwardClear(cleanRobot, initialRoom)) moveF(cleanRobot);
			continue;
		}
	}

	//disPlayRoom(numRows, numCols, initialRoom);

	int numCleaned = countCleaned(numRows, numCols, initialRoom);
	printf("%d\n", numCleaned);

	return 0;
}

void getInput(int& numRows, int& numCols, room& initialRoom, cell& initialCell, int& initialDir)
{
	scanf("%d %d", &numRows, &numCols);
	scanf("%d %d", &initialCell.first, &initialCell.second);
	scanf("%d", &initialDir);
	int currCell;

	for (int row = 0; row < numRows; row++) {
		vector<int> currRow;
		for (int col = 0; col < numCols; col++) {
			scanf("%d", &currCell);
			currRow.push_back(currCell);
		}
		initialRoom.push_back(currRow);
	}

	return;
}

void disPlayRoom(const int numRows, const int numCols, const room& targetRoom)
{
	printf("the room is:\n");
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			printf("%d ", targetRoom[row][col]);
		}
		puts("");
	}

	return;
}

void disPlayRobot(const Robot& targetRobot)
{
	printf("the robot's status:\n");
	printf("in cell (%d, %d)\n", targetRobot.position.first, targetRobot.position.second);
	printf("facing %d\n", targetRobot.direction);

	return;
}

void rotateCcw(Robot& targetRobot)
{
	int ccwDir[4] = {WEST, NORTH, EAST, SOUTH};
	targetRobot.direction = ccwDir[targetRobot.direction];

	return;
}

void moveF(Robot& targetRobot)
{
	int dx[4] = { 0, 1, 0, -1 };
	int dy[4] = { -1, 0, 1, 0 };

	targetRobot.position.first += dy[targetRobot.direction];
	targetRobot.position.second += dx[targetRobot.direction];

	return;
}

void moveB(Robot& targetRobot)
{
	int dx[4] = { 0, -1, 0, 1 };
	int dy[4] = { 1, 0, -1, 0 };

	targetRobot.position.first += dy[targetRobot.direction];
	targetRobot.position.second += dx[targetRobot.direction];

	return;
}

void clean(const Robot& targetRobot, room& targetRoom)
{
	targetRoom[targetRobot.position.first][targetRobot.position.second] = 2;

	return;
}

int isCleaned(const Robot& targetRobot, const room& targetRoom)
{
	return targetRoom[targetRobot.position.first][targetRobot.position.second] == 2;
}

int isAdjEmpty(const Robot& targetRobot, const int numRows, const int numCols, const room& targetRoom)
{
	int dx[4] = { 0, 1, 0, -1 };
	int dy[4] = { -1, 0, 1, 0 };

	int newRow, newCol; 

	for (int dir = 0; dir < 4; dir++) {
		newRow = targetRobot.position.first + dy[dir];
		newCol = targetRobot.position.second + dx[dir];
		if (0 <= newRow && newRow < numRows && 0 <= newCol && newCol < numCols) {
			if (targetRoom[newRow][newCol] == 0) {
				return 1;
			}
		}
	}

	return 0;
}

int isRearClear(const Robot& targetRobot, const room& targetRoom)
{
	int dx[4] = { 0, -1, 0, 1 };
	int dy[4] = { 1, 0, -1, 0 };

	int newRow = targetRobot.position.first + dy[targetRobot.direction];
	int newCol = targetRobot.position.second + dx[targetRobot.direction];

	return ((targetRoom[newRow][newCol]) != 1);
}

int isForwardClear(const Robot& targetRobot, const room& targetRoom)
{
	int dx[4] = { 0, 1, 0, -1 };
	int dy[4] = { -1, 0, 1, 0 };

	int newRow = targetRobot.position.first + dy[targetRobot.direction];
	int newCol = targetRobot.position.second + dx[targetRobot.direction];

	return ((targetRoom[newRow][newCol]) == 0);
}

int countCleaned(const int numRows, const int numCols, const room& targetRoom)
{
	int numCleaned = 0;

	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			if (targetRoom[row][col] == 2) numCleaned++;
		}
	}

	return numCleaned;
}

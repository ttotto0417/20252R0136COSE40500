// https://www.acmicpc.net/problem/17144 air cleaner
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef pair<int, int> cell;
typedef vector<vector<int>> room;

void getInput(room& initialRoom, int r, int c);
void displayRoom(const room& targetRoom, int r, int c);
room spreadDust(const room& targetRoom, int r, int c);
room airCleaner(const room& targetRoom, int r, int c, int cleanerRow);
int countDust(const room& targetRoom, int r, int c);
bool isSpreadable(const room& targetRoom, int r, int c, int targetRow, int targetCol);
int findCleaner(const room& targetRoom, int r, int c);

int main(void)
{
	int r, c, t;
	scanf("%d %d %d", &r, &c, &t);

	room Room;

	getInput(Room, r, c);

	//printf("initial Room:\n");

	//displayRoom(Room, r, c);

	int cleanerRow = findCleaner(Room, r, c);

	for (int time = 0; time < t; time++) {
		//printf("after dust spreading:\n");
		Room = spreadDust(Room, r, c);
		//displayRoom(Room, r, c);

		//printf("after air cleaning:\n");
		Room = airCleaner(Room, r, c, cleanerRow);
		//displayRoom(Room, r, c);

		//printf("number of dust are:\n");
		//printf("%d\n", countDust(Room, r, c));
	}

	printf("%d\n", countDust(Room, r, c));

	return 0;
}

void getInput(room& initialRoom, int r, int c)
{
	int temp;

	for (int row = 0; row < r; row++) {
		vector<int> curRow;

		for (int col = 0; col < c; col++) {
			scanf("%d", &temp);
			curRow.push_back(temp);
		}
		initialRoom.push_back(curRow);
	}

	return;
}

void displayRoom(const room& targetRoom, int r, int c)
{
	for (int row = 0; row < r; row++) {
		for (int col = 0; col < c; col++) {
			printf("%4d", targetRoom[row][col]);
		}
		puts("");
	}

	return;
}

room spreadDust(const room& targetRoom, int r, int c)
{
	room nextRoom = targetRoom;
	int spreadAmount = 0;

	// up down left right
	int dx[4] = { 0, 0, 1, -1 };
	int dy[4] = { 1, -1, 0, 0 };

	for (int row = 0; row < r; row++) {
		for (int col = 0; col < c; col++) {
			if (targetRoom[row][col] > 0) {
				spreadAmount = targetRoom[row][col] / 5;

				for (int dir = 0; dir < 4; dir++) {
					if (isSpreadable(targetRoom, r, c, row + dy[dir], col + dx[dir])) {
						nextRoom[row + dy[dir]][col + dx[dir]] += spreadAmount;
						nextRoom[row][col] -= spreadAmount;
					}
				}
			}

		}
	}
	
	return nextRoom;
}

room airCleaner(const room& targetRoom, int r, int c, int cleanerRow)
{
	room nextRoom = targetRoom;

	// upper cycle : cleanerRow->right->up->left->down

	nextRoom[cleanerRow][1] = 0;

	for (int col = 1; col < c - 1; col++) {
		nextRoom[cleanerRow][col + 1] = targetRoom[cleanerRow][col];
	}

	for (int row = cleanerRow; row > 0; row--) {
		nextRoom[row - 1][c - 1] = targetRoom[row][c - 1];
	}
	
	for (int col = c - 1; col > 0; col--) {
		nextRoom[0][col - 1] = targetRoom[0][col];
	}

	for (int row = 0; row < cleanerRow - 1; row++) {
		nextRoom[row + 1][0] = targetRoom[row][0];
	}

	// lower cycle : cleanerRow + 1->right->down->left->up

	nextRoom[cleanerRow + 1][1] = 0;

	for (int col = 1; col < c - 1; col++) {
		nextRoom[cleanerRow + 1][col + 1] = targetRoom[cleanerRow + 1][col];
	}

	for (int row = cleanerRow + 1; row < r - 1; row++) {
		nextRoom[row + 1][c - 1] = targetRoom[row][c - 1];
	}

	for (int col = c - 1; col > 0; col--) {
		nextRoom[r - 1][col - 1] = targetRoom[r - 1][col];
	}

	for (int row = r - 1; row > cleanerRow + 2; row--) {
		nextRoom[row - 1][0] = targetRoom[row][0];
	}

	return nextRoom;
}

int countDust(const room& targetRoom, int r, int c)
{
	int numDust = 0;

	for (int row = 0; row < r; row++) {
		for (int col = 0; col < c; col++) {
			if (targetRoom[row][col] > 0) numDust += targetRoom[row][col];
		}
	}
	
	return numDust;
}

bool isSpreadable(const room& targetRoom, int r, int c, int targetRow, int targetCol) {
	if (targetRow < 0 || targetRow >= r || targetCol < 0 || targetCol >= c) return 0;

	return (targetRoom[targetRow][targetCol] != -1);
}

int findCleaner(const room& targetRoom, int r, int c)
{
	for (int row = 0; row < r; row++) {
		if (targetRoom[row][0] == -1)  return row;
	}

	return -1;
}

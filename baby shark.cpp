// https://www.acmicpc.net/problem/16236 bfs search with priority queue
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
typedef vector<vector<int>> board;
typedef pair<int, int> cell;
typedef pair<cell, int> cellWithTime;

typedef struct shark {
	cell sharkPos = { -1, -1 };
	int sharkSize = 2;
	int sharkBelly = 0; // number of fish eaten; to track when to grow
} Shark;

void displayBoard(const board& targetBoard);
void displayShark(const Shark& targetShark);
bool isInsideBoard(const board& targetBoard, const cell& targetCell);
bool canPass(const board& targetBoard, const Shark& targetShark, const cell& targetCell);
bool canEatFish(const board& targetBoard, const Shark& targetShark, const cell& targetCell);
cellWithTime findFish(const board& targetBoard, const Shark& targetShark);
void eatFish(board& targetBoard, Shark& targetShark, const cell& fishPos);
void callMom(int time);

int n;

// order should not matter
int dx[4] = { 0, -1, 0, 1 };
int dy[4] = { -1, 0, 1, 0 };

#define EMPTY 0
#define SHARK 9

struct compare { // ordering of cellWithTime, for priorityqueue
	bool operator()(cellWithTime a, cellWithTime b) {
		if (a.second > b.second) return 1;
		if (a.second < b.second) return 0;
		if (a.first.first > b.first.first) return 1;
		if (a.first.first < b.first.first) return 0;
		if (a.first.second > b.first.second) return 1;
		if (a.first.second < b.first.second) return 0;
		return 0;
	}
};

int main(void)
{
	scanf("%d", &n);

	board space;
	Shark babyShark;
	int time = 0;

	int temp;

	for (int i = 0; i < n; i++) {
		vector<int> currRow;
		for (int j = 0; j < n; j++) {
			scanf("%d", &temp);
			currRow.push_back(temp);
			if (temp == 9) {
				babyShark.sharkPos.first = i;
				babyShark.sharkPos.second = j;
			}
		}
		space.push_back(currRow);
	}

	cellWithTime nearestFishWithTime;

	while (1) {
		nearestFishWithTime = findFish(space, babyShark);

		// impossible
		if (nearestFishWithTime.second == -1) break;
		
		time += nearestFishWithTime.second;

		eatFish(space, babyShark, nearestFishWithTime.first);
	}

	// eaten all available fish
	callMom(time);

	return 0;
}

void displayBoard(const board& targetBoard)
{
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			printf("%d ", targetBoard[row][col]);
		}
		puts("");
	}

	return;
}

void displayShark(const Shark& targetShark)
{
	printf("shark is at row %d, col %d\n", targetShark.sharkPos.first, targetShark.sharkPos.second);
	printf("shark has size %d\n", targetShark.sharkSize);
	printf("shark has %d fish in belly\n", targetShark.sharkBelly);

	return;
}

bool isInsideBoard(const board& targetBoard, const cell& targetCell)
{
	if (targetCell.first < 0 || targetCell.second < 0) return 0;

	if (targetCell.first >= n || targetCell.second >= n) return 0;

	return 1;
}

bool canPass(const board& targetBoard, const Shark& targetShark, const cell& targetCell)
{
	return targetShark.sharkSize >= targetBoard[targetCell.first][targetCell.second];
}

bool canEatFish(const board& targetBoard, const Shark& targetShark, const cell& targetCell)
{
	if (targetBoard[targetCell.first][targetCell.second] == EMPTY ||
		targetBoard[targetCell.first][targetCell.second] == SHARK) return 0;

	return targetShark.sharkSize > targetBoard[targetCell.first][targetCell.second];
}

// bfs search to find nearest eatable fish
cellWithTime findFish(const board& targetBoard, const Shark& targetShark)
{
	vector<vector<bool>> visited;

	for (int row = 0; row < n; row++) {
		vector<bool> currRow;
		for (int col = 0; col < n; col++) {
			currRow.push_back(0);
		}
		visited.push_back(currRow);
	}

	// use pq to search (top left)-most cell
	priority_queue<cellWithTime, vector<cellWithTime>, compare> bfsQueue;

	cellWithTime startCellWithTime;
	startCellWithTime.first = targetShark.sharkPos;
	startCellWithTime.second = 0;

	bfsQueue.push(startCellWithTime);

	cellWithTime currCellWithTime;
	cellWithTime nextCellWithTime;

	cellWithTime impossible;
	impossible.first = startCellWithTime.first;
	impossible.second = -1;

	while (!bfsQueue.empty()) {
		currCellWithTime = bfsQueue.top();
		bfsQueue.pop();

		if (canEatFish(targetBoard, targetShark, currCellWithTime.first)) {
			return currCellWithTime;
		}

		for (int dir = 0; dir < 4; dir++) {
			nextCellWithTime.first.first = currCellWithTime.first.first + dy[dir];
			nextCellWithTime.first.second = currCellWithTime.first.second + dx[dir];
			nextCellWithTime.second = currCellWithTime.second + 1;

			if (!isInsideBoard(targetBoard, nextCellWithTime.first)) continue;
			if (!canPass(targetBoard, targetShark, nextCellWithTime.first)) continue;
			if (!visited[nextCellWithTime.first.first][nextCellWithTime.first.second]) {
				visited[nextCellWithTime.first.first][nextCellWithTime.first.second] = 1;

				bfsQueue.push(nextCellWithTime);
			}
		}

	}

	return impossible;
}

// go and eat fish at pos fishPos, update board, update shark
void eatFish(board& targetBoard, Shark& targetShark, const cell& fishPos)
{
	targetBoard[targetShark.sharkPos.first][targetShark.sharkPos.second] = EMPTY;

	targetShark.sharkPos.first = fishPos.first;
	targetShark.sharkPos.second = fishPos.second;

	targetShark.sharkBelly++;
	if (targetShark.sharkBelly == targetShark.sharkSize) {
		targetShark.sharkBelly = 0;
		targetShark.sharkSize++;
	}

	targetBoard[fishPos.first][fishPos.second] = SHARK;

	return;
}

void callMom(int time)
{
	printf("%d\n", time);

	return;
}

// https://www.acmicpc.net/problem/7569 tomato(bfs)

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

typedef struct tomato
{
	int row, col, height;
} Tomato;

typedef std::queue<Tomato> queue;

int main(void)
{
	int numRows, numCols, numBox;
	scanf("%d %d %d", &numCols, &numRows, &numBox);

	int*** storage = (int***)malloc(sizeof(int**) * numBox);
	if (storage == NULL) return -1;

	for (int i = 0; i < numBox; i++) {

		storage[i] = (int**)malloc(sizeof(int*) * numRows);
		if (storage[i] == NULL) return -1;

		for (int j = 0; j < numRows; j++) {
			storage[i][j] = (int*)malloc(sizeof(int) * numCols);
			if (storage[i][j] == NULL) return -1;
		}
	}

	queue bfsQueue;

	for (int height = 0; height < numBox; height++) {
		for (int row = 0; row < numRows; row++) {
			for (int col = 0; col < numCols; col++) {
				scanf("%d", &storage[height][row][col]);
				if (storage[height][row][col] == 1) {
					Tomato tempTomato;
					tempTomato.height = height;
					tempTomato.row = row;
					tempTomato.col = col;
					bfsQueue.push(tempTomato);
				}
			}
		}
	}

	Tomato tempTomato; // for pushing into bfsQueue

	while (!bfsQueue.empty()) {
		int height = bfsQueue.front().height;
		int row = bfsQueue.front().row;
		int col = bfsQueue.front().col;
		bfsQueue.pop();

		if (height != 0) { // has an above cell
			if (storage[height - 1][row][col] == 0) { // above cell is not ripen
				storage[height - 1][row][col] = storage[height][row][col] + 1;
				tempTomato.height = height - 1;
				tempTomato.row = row;
				tempTomato.col = col;
				bfsQueue.push(tempTomato);
			}
		}
		if (height != numBox - 1) { // has a below cell
			if (storage[height + 1][row][col] == 0) { // below cell is not ripen
				storage[height + 1][row][col] = storage[height][row][col] + 1;
				tempTomato.height = height + 1;
				tempTomato.row = row;
				tempTomato.col = col;
				bfsQueue.push(tempTomato);
			}
		}
		if (row != 0) { // has an upper cell
			if (storage[height][row - 1][col] == 0) { // upper cell is not ripen
				storage[height][row - 1][col] = storage[height][row][col] + 1;
				tempTomato.height = height;
				tempTomato.row = row - 1;
				tempTomato.col = col;
				bfsQueue.push(tempTomato);
			}
		}
		if (row != numRows - 1) { // has a lower cell
			if (storage[height][row + 1][col] == 0) { // lower cell is not ripen
				storage[height][row + 1][col] = storage[height][row][col] + 1;
				tempTomato.height = height;
				tempTomato.row = row + 1;
				tempTomato.col = col;
				bfsQueue.push(tempTomato);
			}
		}
		if (col != 0) { // has a left cell
			if (storage[height][row][col - 1] == 0) { // left cell is not ripen
				storage[height][row][col - 1] = storage[height][row][col] + 1;
				tempTomato.height = height;
				tempTomato.row = row;
				tempTomato.col = col - 1;
				bfsQueue.push(tempTomato);
			}
		}
		if (col != numCols - 1) { // has a right cell
			if (storage[height][row][col + 1] == 0) { // right cell is not ripen
				storage[height][row][col + 1] = storage[height][row][col] + 1;
				tempTomato.height = height;
				tempTomato.row = row;
				tempTomato.col = col + 1;
				bfsQueue.push(tempTomato);
			}
		}
	}

	int maxDays = 0;
	int possible = 1;

	for (int height = 0; height < numBox; height++) {
		if (!possible) break;
		for (int row = 0; row < numRows; row++) {
			if (!possible) break;
			for (int col = 0; col < numCols; col++) {
				//printf("%d ", box[row][col]);
				if (storage[height][row][col] == 0) {
					possible = 0;
					break;
				}
				if (storage[height][row][col] > maxDays) maxDays = storage[height][row][col];
			}
			//printf("\n");
		}
	}

	if (!possible) printf("-1\n");
	else printf("%d\n", maxDays - 1);
	return 0;
}

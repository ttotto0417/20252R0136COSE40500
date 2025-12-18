// https://www.acmicpc.net/problem/14502 labatory virus spreading, brute force

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <array>

using namespace std;

typedef vector<vector<int>> lab; // orientation of a lab
typedef pair<int, int> cell; // one cell of a lab
typedef array<cell, 3> cellTriple; // array of 3 cells to build walls

// macros for clearity
#define EMPTY 0
#define WALL 1
#define VIRUS 2

lab spreadVirus(const lab& targetLab, const int numRows, const int numCols); // spread virus in targetLab
int isInside(int row, int col, int numRows, int numCols); // is A[row][col] inside A[numRows][numCols] ?
void displayLab(const lab& targetLab, int numRows, int numCols); // prints lab
int countEmpty(const lab& targetLab, int numRows, int numCols); // count number of empty cells in targetLab
lab buildWalls(const lab& targetLab, cellTriple wallPos, int numRows, int numCols); // build walls to targetLab, in positions wallPos

int main(void)
{
	int labRowNum, labColNum; // number of rows and coloumns of the lab
	scanf("%d %d", &labRowNum, &labColNum);

	lab initialLab; // the shape of lab
	int currStatus; // status of current cell
	vector<cell> emptyCells; // vector containing initially empty cells
	cell currCell; // current cell

	// get lab input from stdin
	for (int row = 0; row < labRowNum; row++) {
		vector<int> currRow;
		for (int col = 0; col < labColNum; col++) {
			scanf("%d", &currStatus);
			currRow.push_back(currStatus);
			// if current cell is empty
			if (currStatus == EMPTY) {
				currCell.first = row;
				currCell.second = col;
				// add to emptyCells
				emptyCells.push_back(currCell);
			}
		}
		initialLab.push_back(currRow);
	}

	int numEmptyCells = (int)emptyCells.size(); // number of initially empty cells

	queue<cellTriple> allWallCombinations; // all possible combinations of cells to build walls
	cellTriple currComb; // current combiantions of cells

	// for all possible combinations
	for (int firstCell = 0; firstCell < numEmptyCells - 2; firstCell++) {
		for (int secondCell = firstCell + 1; secondCell < numEmptyCells - 1; secondCell++) {
			for (int thirdCell = secondCell + 1; thirdCell < numEmptyCells; thirdCell++) {
				currComb[0] = emptyCells[firstCell];
				currComb[1] = emptyCells[secondCell];
				currComb[2] = emptyCells[thirdCell];
				// push current combination
				allWallCombinations.push(currComb);
			}
		}
	}
	/*
	printf("there are %d initially empty cells\nthere are %d all possible wall combinations\n",
		numEmptyCells, (int)allWallCombinations.size());
	*/
	int numAllComb = (int)allWallCombinations.size(); // number of all combinations(should be numEmptycellsC3)
	int maxEmpty = 0; // number of maximum empty cells we can get by building walls
	lab currCombLab; // lab with walls built with current comb
	int currEmptyNum;

	// for all combinations
	for (int combNum = 0; combNum < numAllComb; combNum++) {
		//printf("current combNum is %d\n", combNum);
		currComb = allWallCombinations.front();
		allWallCombinations.pop();
		// build walls
		currCombLab = buildWalls(initialLab, currComb, labRowNum, labColNum);
		//printf("after building walls:\n");
		//displayLab(currCombLab, labRowNum, labColNum);
		// spread virus
		currCombLab = spreadVirus(currCombLab, labRowNum, labColNum);
		//printf("after spreading virus:\n");
		//displayLab(currCombLab, labRowNum, labColNum);
		// count empty cells
		currEmptyNum = countEmpty(currCombLab, labRowNum, labColNum);
		maxEmpty = max(maxEmpty, currEmptyNum);
	}

	printf("%d\n", maxEmpty);

	return 0;
}

lab spreadVirus(const lab& targetLab, const int numRows, const int numCols) // spread virus in targetLab
{
	lab resultLab; // lab with virus spread
	// copy targetLab to resultLab
	resultLab.resize(targetLab.size());
	copy(targetLab.begin(), targetLab.end(), resultLab.begin());

	queue<cell> bfsQueue;
	cell currCell;

	// push initial virus cells to queue
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			if (resultLab[row][col] == VIRUS) {
				currCell.first = row;
				currCell.second = col;
				bfsQueue.push(currCell);
			}
		}
	}

	// up down left right
	int dx[4] = { 0, 0, 1, -1 };
	int dy[4] = { 1, -1, 0, 0 };

	cell frontCell;
	int currRow, currCol;
	cell newCell;
	int newRow, newCol;

	while (!bfsQueue.empty()) {
		// take out first element in queue
		frontCell = bfsQueue.front();
		currRow = frontCell.first;
		currCol = frontCell.second;

		bfsQueue.pop();

		// for cells adjacent to fronCell
		for (int pos = 0; pos < 4; pos++) {
			newRow = currRow + dy[pos];
			newCol = currCol + dx[pos];

			if (isInside(newRow, newCol, numRows, numCols)) {

				// if adjacent cell is empty
				if (resultLab[newRow][newCol] == EMPTY) {
					// change the cell to virus
					resultLab[newRow][newCol] = VIRUS;
					
					// push the cell to queue
					newCell.first = newRow;
					newCell.second = newCol;
					bfsQueue.push(newCell);
				}
			}
		}
	}

	return resultLab;
}

int isInside(int row, int col, int numRows, int numCols) // is A[row][col] inside A[numRows][numCols] ?
{
	return (row >= 0 && row < numRows && col >= 0 && col < numCols);
}

void displayLab(const lab& targetLab, int numRows, int numCols) // prints lab
{
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			printf("%d ", targetLab[row][col]);
		}
		puts("");
	}

	return;
}

int countEmpty(const lab& targetLab, int numRows, int numCols) // count number of empty cells in targetLab
{
	int numEmpty = 0;

	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			if (targetLab[row][col] == EMPTY) numEmpty++;
		}
	}

	return numEmpty;
}

// build walls to targetLab, in positions wallPos
lab buildWalls(const lab& targetLab, cellTriple wallPos, int numRows, int numCols)
{
	lab resultLab; // lab with walls built
	// copy targetLab to resultLab
	resultLab.resize(targetLab.size());
	copy(targetLab.begin(), targetLab.end(), resultLab.begin());

	cell firstCell = wallPos[0];
	cell secondCell = wallPos[1];
	cell thirdCell = wallPos[2];
	/*
	printf("first cell has row %d col %d\n", firstCell.first, firstCell.second);
	printf("second cell has row %d col %d\n", secondCell.first, secondCell.second);
	printf("third cell has row %d col %d\n", thirdCell.first, thirdCell.second);
	*/
	resultLab[firstCell.first][firstCell.second] = WALL;
	resultLab[secondCell.first][secondCell.second] = WALL;
	resultLab[thirdCell.first][thirdCell.second] = WALL;

	return resultLab;
}


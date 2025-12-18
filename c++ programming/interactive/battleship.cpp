// https://www.acmicpc.net/problem/28258 battleship
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

const int numRows = 10;
const int numCols = 10;

int board[numRows][numCols] = { 0, };

void displayBoard(void);
void askLocation(int targetRow, int targetCol);
void displayLocation(int foundRow, int foundCol, int foundRow2, int foundCol2);

int main(void)
{
	int temp;

	int found = 0;
	int found2 = 0;
	int foundRow = 0, foundCol = 0;
	int foundRow2 = 0, foundCol2 = 0;

	// four-ways

	for (int row = 0; row < numRows - 2; row++) {
		for (int col = 0; col < (numCols - 2) / 2; col++) {
			askLocation(row + 1, 2 * col + 1 + row % 2);
			cin >> temp;
			if (temp == 1) {
				found = 1;
				foundRow = row + 1;
				foundCol = 2 * col + 1 + row % 2;
				board[foundRow][foundCol] = 1;
			}
		}
	}

	//displayBoard();

	if (found) // search 3 adj squares
	{
		askLocation(foundRow - 1, foundCol);
		cin >> temp;
		if (temp == 1) {
			found2 = 1;
			foundRow2 = foundRow - 1;
			foundCol2 = foundCol;
		}

		askLocation(foundRow, foundCol - 1);
		cin >> temp;
		if (temp == 1) {
			found2 = 1;
			foundRow2 = foundRow;
			foundCol2 = foundCol - 1;
		}

		askLocation(foundRow, foundCol + 1);
		cin >> temp;
		if (temp == 1) {
			found2 = 1;
			foundRow2 = foundRow;
			foundCol2 = foundCol + 1;
		}

		if (found2 == 0) {
			foundRow2 = foundRow + 1;
			foundCol2 = foundCol;
		}
	
		displayLocation(foundRow, foundCol, foundRow2, foundCol2);
		return 0;
	}

	// three-ways

	// top
	for (int col = 0; col < (numCols - 2) / 2; col++) {
		askLocation(0, col * 2 + 2);
		cin >> temp;
		if (temp == 1) {
			found = 1;
			foundRow = 0;
			foundCol = col * 2 + 2;
			board[foundRow][foundCol] = 1;
		}
	}
	
	if (found) // search 2 adj squares
	{
		askLocation(foundRow, foundCol - 1);
		cin >> temp;
		if (temp == 1) {
			found2 = 1;
			foundRow2 = foundRow;
			foundCol2 = foundCol - 1;
		}

		askLocation(foundRow, foundCol + 1);
		cin >> temp;
		if (temp == 1) {
			found2 = 1;
			foundRow2 = foundRow;
			foundCol2 = foundCol + 1;
		}
		if (found2 == 0) {
			foundRow2 = foundRow + 1;
			foundCol2 = foundCol;
		}
		
		displayLocation(foundRow, foundCol, foundRow2, foundCol2);
		return 0;
	}

	// right
	for (int row = 0; row < (numRows - 2) / 2; row++) {
		askLocation(row * 2 + 1, numCols - 1);
		cin >> temp;
		if (temp == 1) {
			found = 1;
			foundRow = row * 2 + 1;
			foundCol = numCols - 1;
			board[foundRow][foundCol] = 1;
		}
	}

	if (found) // search 2 adj squares
	{
		askLocation(foundRow - 1, foundCol);
		cin >> temp;
		if (temp == 1) {
			found2 = 1;
			foundRow2 = foundRow - 1;
			foundCol2 = foundCol;
		}

		askLocation(foundRow + 1, foundCol);
		cin >> temp;
		if (temp == 1) {
			found2 = 1;
			foundRow2 = foundRow + 1;
			foundCol2 = foundCol;
		}
		if (found2 == 0) {
			foundRow2 = foundRow;
			foundCol2 = foundCol - 1;
		}

		displayLocation(foundRow, foundCol, foundRow2, foundCol2);
		return 0;
	}

	// bottom
	for (int col = 0; col < (numCols - 2) / 2; col++) {
		askLocation(numRows - 1, col * 2 + 1);
		cin >> temp;
		if (temp == 1) {
			found = 1;
			foundRow = numRows - 1;
			foundCol = col * 2 + 1;
			board[foundRow][foundCol] = 1;
		}
	}

	if (found) // search 2 adj squares
	{
		askLocation(foundRow, foundCol - 1);
		cin >> temp;
		if (temp == 1) {
			found2 = 1;
			foundRow2 = foundRow;
			foundCol2 = foundCol - 1;
		}

		askLocation(foundRow, foundCol + 1);
		cin >> temp;
		if (temp == 1) {
			found2 = 1;
			foundRow2 = foundRow;
			foundCol2 = foundCol + 1;
		}
		if (found2 == 0) {
			foundRow2 = foundRow - 1;
			foundCol2 = foundCol;
		}

		displayLocation(foundRow, foundCol, foundRow2, foundCol2);
		return 0;
	}

	// left
	for (int row = 0; row < (numRows - 2) / 2; row++) {
		askLocation(row * 2 + 2, 0);
		cin >> temp;
		if (temp == 1) {
			found = 1;
			foundRow = row * 2 + 2;
			foundCol = 0;
			board[foundRow][foundCol] = 1;
		}
	}

	if (found) // search 2 adj squares
	{
		askLocation(foundRow - 1, foundCol);
		cin >> temp;
		if (temp == 1) {
			found2 = 1;
			foundRow2 = foundRow - 1;
			foundCol2 = foundCol;
		}

		askLocation(foundRow + 1, foundCol);
		cin >> temp;
		if (temp == 1) {
			found2 = 1;
			foundRow2 = foundRow + 1;
			foundCol2 = foundCol;
		}
		if (found2 == 0) {
			foundRow2 = foundRow;
			foundCol2 = foundCol + 1;
		}

		displayLocation(foundRow, foundCol, foundRow2, foundCol2);
		return 0;
	}

	//displayBoard();

	

	// two-ways(corners)

	askLocation(0, 0);
	cin >> temp;

	if (temp == 1) { // upper left corner
		askLocation(0, 1);
		cin >> temp;
		if (temp) displayLocation(0, 0, 0, 1);
		else displayLocation(0, 0, 1, 0);
	}

	else { // lower right corner
		askLocation(numRows - 2, numCols - 1);
		cin >> temp;
		if (temp) displayLocation(numRows - 2, numCols - 1, numRows - 1, numCols - 1);
		else displayLocation(numRows - 1, numCols - 2, numRows - 1, numCols - 1);
	}

	return 0;
}

void displayBoard(void)
{
	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			printf("%2d", board[row][col]);
		}
		puts("");
	}
	
	return;
}

void askLocation(int targetRow, int targetCol)
{
	cout << "? " << targetRow << " " << targetCol << endl;

	return;
}

void displayLocation(int foundRow, int foundCol, int foundRow2, int foundCol2)
{
	cout << "! " << foundRow << " " << foundCol << " " << foundRow2 << " " << foundCol2 << endl;

	return;
}

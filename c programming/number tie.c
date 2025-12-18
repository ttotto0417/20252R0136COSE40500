// https://www.acmicpc.net/problem/1744 number tie
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int compare(const int* a, const int* b);

int main(void)
{
	int testnum;
	scanf("%d", &testnum);

	int* numbers = (int*)malloc(sizeof(int) * testnum);
	if (numbers == NULL) return -1;

	int isZero = 0;
	int posCount = 0;
	int negCount = 0;
	int oneCount = 0;

	for (int i = 0; i < testnum; i++) {
		int temp;
		scanf("%d", &temp);
		numbers[i] = temp;
		if (temp == 0) isZero = 1;
		else if (temp == 1) oneCount++;
		else if (temp > 1) posCount++;
		else if (temp < 0) negCount++;
	}

	qsort(numbers, testnum, sizeof(int), compare);

	long sum = 0;

	for (int i = 0; i < posCount / 2; i++) {
		sum += (long)numbers[2 * i] * numbers[2 * i + 1];
		//printf("at pos %d, %ld is added\n", 2 * i, (long)numbers[2 * i] * numbers[2 * i + 1]);
	}
	if (posCount % 2) {
		sum += (long)numbers[posCount - 1];
		//printf("at pos %d, %ld is added\n", posCount - 1, (long)numbers[posCount - 1]);
	}

	for (int i = 0; i < negCount / 2; i++) {
		//printf("at pos %d, %ld is added\n", posCount + oneCount + 2 * i, (long)numbers[posCount + oneCount + 2 * i] * numbers[posCount + oneCount + 2 * i + 1]);
		sum += (long)numbers[posCount + oneCount + 2 * i] * numbers[posCount + oneCount + 2 * i + 1];
	}
	if (isZero == 0 && negCount % 2)
	{
		//printf("no 0, %d is added\n", numbers[posCount + oneCount + negCount - 1]);
		sum += (long)numbers[posCount + oneCount + negCount - 1];
	}
	sum += oneCount;
	//printf("%d 1 is added\n", oneCount);
	printf("%ld\n", sum);

	return 0;
} // 양수를 내림차순으로 정렬해 앞에서부터 두개씩 곱하고 하나가 남으면 그냥 더한다.
// 음수를 오름차순으로 정렬해 앞에서부터 두개씩 곱한다.
// 음수가 하나 남았을때 0이 있으면 곱하고 없으면 그냥 더한다.
// 양수 내림차순 음수 오름차순 0 순서로 정렬

int compare(const int *a, const int *b)
{
	if (*a == *b) return 0;
	if (*a > 0 && *b > 0) {
		if (*a > *b) return -1;
		return 1;
	}
	if (*a < 0 && *b < 0) {
		if (*a > *b) return 1;
		return -1;
	}
	if (*a == 0 && *b != 0) {
		return 1;
	}
	if (*a != 0 && *b == 0) {
		return -1;
	}
	if (*a > *b) return -1;
	if (*a < *b) return 1;
	return 0;
}
// https://www.acmicpc.net/problem/2457 princess garden
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int monthDays[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int numDays(int month, int day);


typedef struct flower {
	int begin;
	int end;
} Flower;
int compare(const Flower* a, const Flower* b);
int main(void)
{
	int n;
	scanf("%d", &n);
	Flower* flowers = (Flower*)malloc(sizeof(Flower)*n);
	if (flowers == NULL) return -1;

	for (int i = 0; i < n; i++) {
		int m1, d1, m2, d2;
		scanf("%d %d %d %d", &m1, &d1, &m2, &d2);
		Flower* tempFlower = malloc(sizeof(Flower));
		if (tempFlower == NULL) return -1;

		tempFlower->begin = numDays(m1, d1);
		tempFlower->end = numDays(m2, d2);
		flowers[i] = *tempFlower;
	}
	
	qsort(flowers, n, sizeof(Flower), compare);

	int currentDay = numDays(12, 1);
	int beginday = numDays(3, 1);
	int flowerCount = 0;
	while (currentDay > beginday) {
		//printf("currentDay is %d\n", currentDay);
		int minBegin = 9999;
		int selected = -1;
		for (int i = 0; i < n; i++) {
			if (flowers[i].begin >= currentDay) continue;
			if (flowers[i].end >= currentDay && flowers[i].begin < minBegin) { // select the least begin, where end > currentday
				selected = i;
				minBegin = flowers[i].begin;
			}
		}
		//printf("flowers[%d] is selected, count is %d\n", selected, flowerCount);
		if (selected != -1) {
			//printf("flowers[%d] is selected, count is %d\n", selected, flowerCount);
			currentDay = flowers[selected].begin;
			flowerCount++;

		}
		else {
			flowerCount = 0;
			break;
		}
	}
	
	printf("%d\n", flowerCount);

	return 0;
}

int numDays(int month, int day)
{
	int count = day;
	for (int i = 0; i < month; i++) {
		count += monthDays[i];
	}
	return count;
}

int compare(const Flower* a, const Flower* b)
{
	if (a->end > b->end) return -1;
	if (a->end < b->end) return 1;
	if (a->begin > b->begin) return 1;
	if (a->begin < b->begin) return -1;
	return 0;
}
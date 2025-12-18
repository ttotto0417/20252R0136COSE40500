// https://www.acmicpc.net/problem/1744 number tie
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct class {
	long begin;
	long end;
} Class;

int compare(const Class* a, const Class* b);

int main(void)
{
	long n;
	scanf("%ld", &n);

	long* classroom = (long*)malloc(sizeof(long) * n);
	if (classroom == NULL) return -1;

	memset(classroom, 0, n * sizeof(long));

	Class* classes = (Class*)malloc(sizeof(Class) * n);
	if (classes == NULL) return -1;

	for (long i = 0; i < n; i++) {
		long tempBegin, tempEnd;
		scanf("%ld %ld", &tempBegin, &tempEnd);
		Class *tempClass = (Class*)malloc(sizeof(Class));
		if (tempClass == NULL) return -1;

		tempClass->begin = tempBegin;
		tempClass->end = tempEnd;
		classes[i] = *tempClass;
	}

	qsort(classes, n, sizeof(Class), compare);

	Class curClass = classes[0];
	for (long i = 0; i < n; i++) {
		curClass = classes[i];
		for (long j = 0; j < n; j++) {
			if (curClass.begin >= classroom[j]) {
				classroom[j] = curClass.end;
				break;
			}
		}
	}

	long numClassroom = 0;
	for (long i = 0; i < n; i++) {
		if (classroom[i] != 0) numClassroom++;
	}

	printf("%ld\n", numClassroom);

	return 0;
}

int compare(const Class* a, const Class* b)
{
	if (a->begin > b->begin) return 1;
	if (a->begin < b->begin) return -1;
	if (a->end > b->end) return 1;
	if (a->end < b->end) return -1;
	
	return 0;
}

/* classroom을 n개 만들어 놓고 0으로 초기화, 수업을 시작 시간 순으로 정렬.
* 각 수업마다: classroom을 앞에서부터 보면서 classroom[i]가 수업.시작 보다 작거나 같으면 
* 거기에 넣고 classroom[i]를 수업.끝으로 바꿈.
* classroom 중 0이 아닌 개수를 출력
*/

// nlogn으로 짜야함. 배정될 강의실을 찾을 때 binary search를 해야 하는데,
// classroom을 heap같은데 넣어서 정렬되게 하고 logn으로 찾아야 함.
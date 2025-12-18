// https://www.acmicpc.net/problem/1931 meeting assign
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct meeting {
	long long begin;
	long long end;
} Meeting;

int compMeet(const Meeting* a, const Meeting* b);

int main(void)
{
	long n;
	scanf("%ld", &n);
	Meeting* meetings = malloc(sizeof(Meeting) * n); // store struct meeting's
	if (meetings == NULL) return -1;

	for (long i = 0; i < n; i++) {
		long long tempb, tempe;
		scanf("%lld %lld", &tempb, &tempe);

		Meeting *tempMeeting = malloc(sizeof(Meeting));
		if (tempMeeting == NULL) return -1;

		tempMeeting->begin = tempb;
		tempMeeting->end = tempe;
		meetings[i] = *tempMeeting;
	}

	qsort(meetings, n, sizeof(Meeting), compMeet);

	long long currentTime = 0;
	long numMeet = 0;
	Meeting currentMeet;

	for (long i = 0; i < n; i++) {
		//printf("%lld %lld\n", meetings[i].begin, meetings[i].end);
		currentMeet = meetings[i];
		if (currentTime <= currentMeet.begin) {
			numMeet++;
			currentTime = currentMeet.end;
		}
	}

	printf("%ld\n", numMeet);

	return 0;
}

int compMeet(const Meeting* a, const Meeting* b)
{
	if (a->end > b->end) return 1;
	if (a->end < b->end) return -1;
	if (a->begin > b->begin) return 1;
	if (a->begin < b->begin) return -1;
	return 0;
}
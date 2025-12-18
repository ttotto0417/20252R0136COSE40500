// https://www.acmicpc.net/problem/2675 string repetition

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	unsigned int testnum = 0;
	scanf("%u", &testnum);
	
	unsigned int *numbers;
	numbers = (unsigned int *)malloc(sizeof(int) * testnum);
	char **strings;
	strings = (char **)malloc(sizeof(char*) * testnum);
	for (unsigned int i = 0; i < testnum; i++) {
		strings[i] = (char *)malloc(sizeof(char) * 21);
	}

	for (unsigned int i = 0; i < testnum; i++) {
		/*
		printf("i is %u\n", i);
		if (i == 1) {
			printf("string[0] is %s\n", strings[0]);
		}*/
		int repeat;
		scanf("%d", &repeat);
		numbers[i] = repeat;
		//printf("number of repeats is %d\n", repeat);
		
		char a;
		for (unsigned int j = 0; j < 20; j++) {
			a = getchar();
			//printf("the character is %c\n", a);
			if (a == ' ') {
				j--;
				continue;
			}
			if (a == '\n') {
				strings[i][j] = '\0';
				break;
			}
			strings[i][j] = a;
		}
		/* 
		printf("the string is %s\n", strings[i]);
		if (i == 1) {
			printf("string[0] is %s\n", strings[0]);
		}*/
	}
	/*
	for (unsigned int i = 0; i < testnum; i++) {
		printf("%uth string is %s", i, strings[i]);
	} */

	for (unsigned int i = 0; i < testnum; i++) {
		for (unsigned int j = 0; j < strlen(strings[i]); j++) {
			//printf("\ni is %u j is %u\n", i, j);
			for (unsigned int k = 0; k < numbers[i]; k++) {
				putchar(strings[i][j]);
			}
		}
		putchar('\n');
	}


	return 0;
}
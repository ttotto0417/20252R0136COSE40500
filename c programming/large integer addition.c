// https://www.acmicpc.net/problem/10757 large integer addition
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char a[10002], b[10002];
	char temp;
	int count = 0;
	while ((temp = getchar()) != ' ') {
		a[count] = temp;
		count++;
	}
	a[count] = '\0';
	count = 0;
	while ((temp = getchar()) != '\n') {
		b[count] = temp;
		count++;
	}
	b[count] = '\0';
	//printf("%s\n%s\n", a, b);

	int alen = (int)strlen(a);
	int blen = (int)strlen(b);
	//printf("alen is %d blen is %d\n", alen, blen);
	//printf("a is %s\nb is %s\n", a, b);
	int carry = 0;
	char* result;
	if (alen > blen) {
		result = (char *)malloc(sizeof(char) * (alen + 1));
		if (result == NULL) return -1;
		result[alen] = '\0';
		for (int i = 0; i < alen; i++) {
			if (i >= blen) { // only consider a
				//puts("i >= blen");
				int tempa = a[alen - i - 1] - '0';
				//printf("tempa is %d\n", tempa);
				result[alen - i - 1] = ( (tempa + carry) % 10 ) + '0';
				//printf("result [%d] is %c\n", alen - i - 1, ((tempa + carry) % 10) + '0');
				carry = (tempa + carry) / 10;
				//printf("carry is %d\n", carry);
			}
			else {
				//puts("i < blen");
				int tempa = a[alen - i - 1] - '0';
				int tempb = b[blen - i - 1] - '0';
				//printf("tempa is %d tempb is %d\n", tempa, tempb);
				result[alen - i - 1] = ((tempa + tempb + carry) % 10) + '0';
				//printf("result [%d] is %c\n", alen - i - 1, ((tempa + tempb + carry) % 10) + '0');
				carry = (tempa + tempb + carry) / 10;
				//printf("carry is %d\n", carry);
			}
		}
		if (carry) printf("1");
		printf("%s\n", result);
		
	}
	else {
		result = (char*)malloc(sizeof(char) * (blen + 1));
		if (result == NULL) return -1;
		result[blen] = '\0';
		for (int i = 0; i < blen; i++) {
			if (i >= alen) { // only consider b
				//puts("i >= alen");
				int tempb = b[blen - i - 1] - '0';
				//printf("tempa is %d\n", tempa);
				result[blen - i - 1] = ((tempb + carry) % 10) + '0';
				//printf("result [%d] is %c\n", alen - i - 1, ((tempa + carry) % 10) + '0');
				carry = (tempb + carry) / 10;
				//printf("carry is %d\n", carry);
			}
			else {
				//puts("i < alen");
				int tempa = a[alen - i - 1] - '0';
				int tempb = b[blen - i - 1] - '0';
				//printf("tempa is %d tempb is %d\n", tempa, tempb);
				result[blen - i - 1] = ((tempa + tempb + carry) % 10) + '0';
				//printf("result [%d] is %c\n", alen - i - 1, ((tempa + tempb + carry) % 10) + '0');
				carry = (tempa + tempb + carry) / 10;
				//printf("carry is %d\n", carry);
			}
		}
		if (carry) printf("1");
		printf("%s\n", result);
	}

	return 0;
}
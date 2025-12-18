// https://www.acmicpc.net/problem/11444 fibonacci O(logn) using dnc
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

long long p = 1000000007;

typedef struct mat2 {
	long long a11, a12, a21, a22;
} Mat2;

Mat2 mat2Mult(Mat2 a, Mat2 b);

Mat2 matPow(Mat2 a, long long n);

int main(void)
{
	long long n;
	scanf("%lld", &n);

	if (n == 0) {
		printf("0\n");
		return 0;
	}
	
	Mat2 initialMat;
	initialMat.a11 = 1;
	initialMat.a12 = 1;
	initialMat.a21 = 1;
	initialMat.a22 = 0;

	initialMat = matPow(initialMat, n);
	printf("%lld\n", initialMat.a21);

	return 0;
}

Mat2 mat2Mult(Mat2 a, Mat2 b) // 2*2 matrix multiplication mod 
{
	Mat2 resultMat;

	resultMat.a11 = (a.a11 * b.a11 + a.a12 * b.a21) % p;
	resultMat.a12 = (a.a11 * b.a12 + a.a12 * b.a22) % p;
	resultMat.a21 = (a.a21 * b.a11 + a.a22 * b.a21) % p;
	resultMat.a22 = (a.a21 * b.a12 + a.a22 * b.a22) % p;

	return resultMat;
}

Mat2 matPow(Mat2 a, long long n) // a^n
{
	a.a11 %= p;
	a.a12 %= p;
	a.a21 %= p;
	a.a22 %= p;

	if (n == 1) return a;

	Mat2 half = matPow(a, n / 2);

	if (n % 2 == 0) {
		return mat2Mult(half, half);
	}
	else {
		return mat2Mult(mat2Mult(half, half), a);
	}
}

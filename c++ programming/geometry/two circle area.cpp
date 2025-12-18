// https://www.acmicpc.net/problem/7869 area between two circles
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
	double x1, y1, r1, x2, y2, r2;

	scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &r1, &x2, &y2, &r2);

	double dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

	double area = 0.0;

	double pi = 3.1415926;

	if (r1 + r2 <= dist) area = 0.0;

	else if (fabs(r1 - r2) >= dist) area = pi * min(r1, r2) * min(r1, r2);

	else {
		double theta1 = 2.0 * acos( (dist * dist + r1 * r1 - r2 * r2) / (2.0 * dist * r1));
		double theta2 = 2.0 * acos((dist * dist + r2 * r2 - r1 * r1) / (2.0 * dist * r2));

		area = 0.5 * (r1 * r1 * (theta1 - sin(theta1)) + r2 * r2 * (theta2 - sin(theta2)));
	}

	printf("%.3f\n", area);

	return 0;
}

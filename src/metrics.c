#include "metrics.h"
#include <math.h>

float brightness_average(int r, int g, int b)
{
	return (r+g+b)/3;
}


float brightness_humanized(int r, int g, int b)
{
	return 0.21*r + 0.72*g + 0.07*b;
}

float gradient_sqrt(int p, int q)
{
	return sqrt(p*p + q*q);
}

float gradient_abs(int p, int q)
{
	return abs(p) + abs(q);
}

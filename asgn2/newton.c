#include <stdio.h>
#include "mathlib.h"
#include <stdlib.h>

static int iters = 0;
double sqrt_newton(double x){
	iters = 0;
	double temp = 0.0;
	double sqrt = 1.0;
	while(absolute(sqrt - temp) > EPSILON){
		temp = sqrt;
		sqrt = 0.5 * (temp + x / sqrt);
		iters += 1;
	}
	return sqrt;
}

int sqrt_newton_iters() {
	return iters;
}

int main(void){
	printf("%16.15lf\n", sqrt_newton(25));
	printf("%d\n", iters);
}

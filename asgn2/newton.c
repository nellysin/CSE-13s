#include <stdio.h>
#include "mathlib.h"
#include <stdlib.h>

static int iters = 0;
double sqrt_newton(double x){
	iters = 0;
	double temp = 0.0;
	double s = 1.0;
	while(absolute(s - temp) > EPSILON){ //CITED: Professor Long for newton's squareroot sudo code
		temp = s;
		s = 0.5 * (temp + x / s);
		iters += 1;
	}
	return s;
}

int sqrt_newton_iters() {
	return iters;
}

#include "mathlib.h"
#include <stdio.h>
#include <stdlib.h>

static int madhava_terms = 0;
double pi_madhava(){
	madhava_terms = 0;
	double k = 0.0;
	double three = 1.0;
	double madhava = 0.0;
	double n = 0.0;
	while(three >= EPSILON){
		k += (2.0 * n + 1.0) * three;
		three /= (-3.0);
		n += 1.0;
		madhava_terms += 1;
	}
	madhava = k * sqrt_newton(12);
	return madhava;
}

int pi_madhava_terms(){
	return madhava_terms;
}

int main(void){
	printf("%16.15lf\n", pi_madhava());
	printf("%d\n", pi_madhava_terms());
	return 0;
}

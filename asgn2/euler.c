#include <stdio.h>
#include "mathlib.h"
#include <stdlib.h>

static int euler_term = 0;
double pi_euler(){
	euler_term = 0;
	double k = 1.0;		// answer -> will use for incrementation
	double n = 1.0;		// n = check
	double d_k = 0.0;	//multiply k by itself
	double euler = 0.0;
	double sum = 0.0;	// summation
	while(n >= EPSILON){	// until n reaches close to epsilon
		d_k = k * k;	
		n = 1.0/d_k;
		sum += 1.0/d_k;
		k += 1.0;
		euler_term += 1;
	}
	euler = sqrt_newton(6.0*sum); // equation outside the summation
	return euler;

}

int pi_euler_terms(){
	return euler_term;
}

#include <stdio.h>
#include "mathlib.h"
#include <stdlib.h>

static int euler_term = 0;
double pi_euler(){
	euler_term = 0;
	double k = 1.0;
	double n = 0.0;
	double euler = 0.0;
	while(n > EPSILON){
		n = ((1.0/k) * (1/k));
		k += ((1.0/k) * (1/k));
	}
	euler = 6 * k;
	euler = sqrt_newton(euler);
	return euler;

}

int pi_euler_terms(){
	return euler_term;
}

int main(void){
	printf("%15.16lf\n", pi_euler());
	return 0;
}

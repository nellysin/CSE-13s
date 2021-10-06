#include <stdio.h>
#include "mathlib.h"
#include <stdlib.h>

static int euler_term = 0;
double pi_euler(){
	euler_term = 0;
	double k = 1.0;
	double n = 1.0;
	double d_k = 0.0;
	double euler = 0.0;
	double sum = 0.0;
	while(n > EPSILON){
		d_k = k * k;
		n = 1.0/d_k;
		sum += 1.0/d_k;
		k += 1.0;
		euler_term += 1;
	}
	euler = sqrt_newton(6.0*sum);
	return euler;

}

int pi_euler_terms(){
	return euler_term;
}

int main(void){
	printf("%15.16lf\n", pi_euler());
	printf("%d\n", pi_euler_terms());
	return 0;
}

#include "mathlib.h"
#include <stdio.h>
#include <stdlib.h>

static int viete_factors = 0;
double pi_viete(){
        viete_factors = 0;
        double k = 2.0;
//	double n = 1.0;
        double viete = 1.0;
        while(k >= EPSILON){
		k = sqrt_newton(k);
		viete *= k;
		viete_factors += 1;
		printf("%f", k);
	}
	viete = 2 / viete;
        return viete;
}

int pi_viete_factors(){
        return viete_factors;
}

int main(void){
        printf("%16.15lf\n", pi_viete());
        printf("%d\n", pi_viete_factors());
        return 0;
}

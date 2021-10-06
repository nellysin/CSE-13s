#include "mathlib.h"
#include <stdio.h>
#include <stdlib.h>

static int viete_factors = 0;
double pi_viete(){
        viete_factors = 0;
        double k = sqrt_newton(2.0);
        double viete = sqrt_newton(2.0)/2.0;
        while(absolute(k/2.0 - 1) >= EPSILON){ // while n approches EPSILON
		k = sqrt_newton(2.0 + k);
		viete *= k/2.0;

		viete_factors += 1; 
	}
	viete = 2.0 / viete;
        return viete;
}

int pi_viete_factors(){
        return viete_factors;
}

/*int main(void){
        printf("%16.15lf\n", pi_viete());
        printf("%d\n", pi_viete_factors());
        return 0;
}*/

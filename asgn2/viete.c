#include "mathlib.h"
#include <stdio.h>
#include <stdlib.h>

static int viete_factors = 0;
double pi_viete(){
        viete_factors = 0;
        double k = 1.0;
        double viete = 0.0;
	double n = 1.0;
        while(n >= EPSILON){
                n = 2.0/k;
		viete += n;
		k += 1.0;
		viete_factors += 1;
        }
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


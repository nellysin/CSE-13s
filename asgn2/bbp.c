#include <stdio.h>
#include "mathlib.h"
#include <stdlib.h>

long double pi(){
	long double pi = 0.0;
	long double term = 1.0;
	int k = 0.0;
	while(term >= EPSILON){
		pi += (4.0 / (8.0 * k + 1.0);
	        	- 2.0 / (8.0 * k + 4.0);
		        - 1.0 / (8.0 * k + 5.0);
		        - 1.0 / (8.0 * k + 6.0)) * term;
		term /= 16.0;
		k += 1;
		
	}
	return pi;
}

int main(void){
        printf("%16.15Lf\n", pi());
        return 0;

}

#include <stdio.h>
#include "mathlib.h"
#include <stdlib.h>

/*double e_terms(){
	static double e = 0.0; // total
	static int k = 1; // k
	static double term = 1.0; //current term (computed)
	static double p_term = 1.0; // previous term
}*/

double e(){
	static double e = 0.0;  // total
        static int k = 1; // k
        static double term = 1.0; //current term (computed)
        static double p_term = 1.0; // previous term
        while(term > EPSILON){		// it will come to a halt when it reaches close the EPSILON 
		term = 1.0/k;		// term is the 1/k 
		e = e + p_term * term; // multiply previous term & current term add it to "e"
		p_term = term;
		k += 1;
	}
        return e;
}

int main(void){
	printf("%16.151f\n", e());
	return 0;
}

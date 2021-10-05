#include <stdio.h>
#include "mathlib.h"
#include <stdlib.h>

int e_terms(){
	static double e = 1.0; // total
	static double term = 1.0; //current term (computed)
	static double p_term = 1.0; // previous term
	int static k = 1;
	return e;
	return term;
	return p_term;
	return k;
}


double e(){
	double e = 1.0;  // total
        int k = 1; // k
        double term = 1.0; //current term (computed)
        double p_term = 1.0;
	e_terms();
        while(term > EPSILON){		// it will come to a halt when it reaches close the EPSILON 
		term = term * (p_term / k);
		e += term;	 
		k += 1;
	}
	return e;
}

int main(void){
	printf("%16.15lf\n", e());
	return 0;
}

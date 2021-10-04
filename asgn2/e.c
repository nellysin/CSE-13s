#include <stdio.h>
#include "mathlib.h"
#include <stdlib.h>

#define EPSILON 1e-14

double e(){
	static double e = 0.0;
	int k = 0;
	double term = 1.0;
	double p_term = 0.0;
        while(term > EPSILON){
		if(k == 0 || k == 1){
			p_term = 1;
			e += p_term;
		}
		else{
			term = 1/k;
			e += p_term * term;
			p_term = term;
		}
		k += 1;
	}
        return e;
}

//double e_terms(){
//	static double e = 0.0;
//}

int main(void){
	printf("%16.151f\n", e());
}

#include <stdio.h>
#include "mathlib.h"
#include <stdlib.h>


static int term = 0;
double e(){
	term = 0;
	double e = 1.0;  // total
        int k = 1; // k
        double c_term = 1.0; //current term (computed)
        double p_term = 1.0;
        while(c_term > EPSILON){		// it will come to a halt when it reaches close the EPSILON 
		c_term = c_term * (p_term / k);
		e += c_term;	 
		k += 1;
		term += 1;
	}
	return e;
}

int e_terms(){
        return term;
}



/*int main(void){
	printf("%16.15lf\n", e());
	printf("%d\n", e_terms());
	return 0;
}*/

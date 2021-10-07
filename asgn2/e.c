#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int e_term = 0; //CITED: Prof long for equation
double e() {
    e_term = 0;
    double e = 1.0; // total
    int k = 1; // k
    double c_term = 1.0; //current term (computed)
    double p_term = 1.0;
    while (c_term > EPSILON) { // it will come to a halt when it reaches close the EPSILON
        c_term = c_term * (p_term / k);
        e += c_term;
        k += 1;
        e_term += 1;
    }
    return e;
}

int e_terms() {
    return e_term;
}

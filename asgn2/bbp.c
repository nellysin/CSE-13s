#include "mathlib.h"
#include <stdio.h>
#include <stdlib.h>

static int bbp_term = 0;

double pi_bbp() {
    bbp_term = 0;
    double p = 0.0;
    double k = 1.0;
    double n = 0.0;

    while (k >= EPSILON) {
	p += (4.0 / (8.0 * n + 1.0) - 2.0 / (8.0 * n + 4.0) - 1.0 / (8.0 * n + 5.0) - 1.0 / (8.0 * n + 6.0)) * k; // equation for bbp pi
	k /= 16.0; //16^-k
	n += 1; //increment by 1
	bbp_term += 1; // for counting terms in bbp_pi
    }
    return p;
}

int pi_bbp_terms() {
    return bbp_term;
}

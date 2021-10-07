#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int viete_factors = 0; //CITED: Prof long for equation
double pi_viete() {
    viete_factors = 0;
    double k = sqrt_newton(2.0);
    double viete = sqrt_newton(2.0) / 2.0; // CITED: MILES (tutoring section) usage of absolute
    while (absolute(k / 2.0 - 1) >= EPSILON) { // while k approches EPSILON
        k = sqrt_newton(2.0 + k);
        viete *= k / 2.0;

        viete_factors += 1;
    }
    viete = 2.0 / viete;
    return viete;
}

int pi_viete_factors() {
    return viete_factors;
}

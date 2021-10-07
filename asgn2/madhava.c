#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int madhava_terms = 0; //CITED: Prof long for equation
double pi_madhava() {
    madhava_terms = 0;
    double k = 1.0;
    int n = 0;
    double three = 1.0;
    double madhava = 0.0;
    double i = 0.0;
    double stop = 1.0;
    while (stop >= EPSILON) { //get close to EPSILON as possible
        if (n % 2 == 0) { // alternate between -3 and 3 if n is odd or even
            if (n == 0) {
                madhava += three / (2.0 * i + 1.0);
            } else {
                k /= (3.0);
                three /= (3.0);
                madhava += three / (2.0 * i + 1.0);
                stop = k / (2.0 * i + 1.0);
            }
        } else if (n % 2 == 1) {
            k /= (3.0);
            three /= (3.0);
            madhava -= three / (2.0 * i + 1.0);
            stop = k / (2.0 * i + 1.0);
        }
        i += 1.0;
        n += 1;
        madhava_terms += 1;
    }
    madhava *= sqrt_newton(12);
    return madhava;
}

int pi_madhava_terms() {
    return madhava_terms;
}

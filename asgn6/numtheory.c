#include "numtheory.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_t v, p, odd; //initialize v and p
    mpz_init_set_ui(v, 1); //initialize the set of v with 1
    mpz_init_set(p, base); //initialize the set with the base
    while (mpz_cmp_ui(exponent, 0) > 0) { //compare the exponent to be greater than 0
        //mpz_mod_ui(odd, exponent, 2);
        if (1 == mpz_mod_ui(odd, exponent, 2)) { //if the exponent is odd
            mpz_mul(v, v, p); //do operation v = v x p
            mpz_mod(v, v, modulus); //and find the modulus of that
        }
        mpz_mul(p, p, p); //multiply the p with itself
        mpz_mod(p, p, modulus); //and assgn it to the modulus of n
        mpz_divexact_ui(exponent, exponent, 2); //divide d by 2
    }
    return v; // find a way to store the computed result in out.
}

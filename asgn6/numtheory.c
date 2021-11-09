#include "numtheory.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_t v, p;
    mpz_init_set_ui(v, 1);
    mpz_init_set(p, base);
    while (mpz_cmp_ui(exponent, 0)) {
        if (1 == gmp_mod(exponent, 2)) {
            x = mpz_mul(x, p);
            x = gmp_mod(modulus);
        }
        p = mpz_mul(p, p);
        p = gmp_mod(modulus);
        exponent = gmp_div_q(exponent, 2);
    }
    return v;
}

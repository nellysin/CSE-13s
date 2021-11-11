#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include "rsa.h"

//CITE: Professor Long (assgn doc)
//CITE: TA Eugene (structure) (11/9 section)
//CITE: Tutor Eric (rsa_make_pub) (11/10 session)

//void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
//    uint64_t pbits = (random() % (nbits / 2))
//                     + (nbits / 4); //calculating the num of bits we will be passing (asgn doc)
//    uint64_t qbits = nbits - pbits; // you cannot stop to a lower bound and end in upper bound
//    make_prime(p, pbits, iters);
//    make_prime(q, qbits, iters);
//    mpz_sub_ui(p_min, p, 1); //initiliaze p_min
//    mpz_sub_ui(q_min, q, 1); //initiliaze q_min
//    mpz_mul(n, p_min, q_min); // the computed totient
//    do {
//        mpz_urandom(e, state, nbits);
        //gcd(gcd_e_tn, e, n) //the totient
//    } while (mpz_cmp_ui(gcd_e_tn, 1));
    //clearing the memory
//}

//the user name is passed in -- rsa pub
//getenv()
//$USER

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>

#include "numtheory.h"
#include "randstate.h"

//gmp_randstate_t state;

//CITE: Professor Long (pseudo for number theory)
//CITE: TA Eugene (structure) (11/9 section)
//CITE: Tutor Miles (is_prime & make prime) (11/10 session)
//CITE: Tutor Eric (is_prime & make prime) (11/10 session)

void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n) {
    mpz_t v, p, odd; //initialize v and p
    mpz_init(odd);
    mpz_init_set_ui(v, 1); //initialize the set of v with 1
    mpz_init_set(p, a); //initialize the set with the base
    while (mpz_cmp_ui(d, 0) > 0) { //compare the exponent to be greater than 0
        if (1 == mpz_mod_ui(odd, d, 2)) { //if the exponent is odd
            mpz_mul(v, v, p); //do operation v = v x p
            mpz_mod(v, v, n); //and find the modulus of that
        }
        mpz_mul(p, p, p); //multiply the p with itself
        mpz_mod(p, p, n); //and assgn it to the modulus of n
        mpz_fdiv_q_ui(d, d, 2); //divide d by 2
    }
    mpz_set(o, v); //store the computed result in out.
    mpz_clears(v, p, odd, NULL); //no memory leak
}

bool is_prime(mpz_t n, uint64_t iters) {
    mpz_t n_minus, r, two; //initialize the mpz

    //mpz_init(n); //initializing
    //this is for writing n - 1 = 2^s(r) such that r is odd
    mpz_inits(n_minus, r, two, NULL);

    mpz_sub_ui(n_minus, n, 1); //this will be n - 1

    mp_bitcnt_t s = 2; //this is just a bit counter -- in 2^s
    mpz_set_ui(two, 2); //setting an mpz_t dedicated to 2
    //such that r is odd
    
    if(mpz_cmp_ui(n, 2) < 0 || (mpz_cmp_ui(n, 4) == 0)){ //M Rambin only works for n > 2 and 4 fails 
        return false;
    }
    if(mpz_cmp_ui(n, 4) < 0){ // 3 is prime but it would still fail (considering range is {2 ... n - 2})
        return true;
    }

    while (mpz_divisible_2exp_p(n_minus, s)) { // n-1 / 2^s = r
        s += 1; //then increment the s
    }
    s -= 1; // b/c 0 < r < s - 1

    mpz_tdiv_q_2exp(r, n_minus, s); //storing it to r = (n-1)/ 2^s

    mpz_t a, bound, y, j; //we need a bound because we want a to be between 2 to n - 1
    mpz_inits(a, bound, y, j, NULL); // another set of initialization

    for (uint64_t i = 0; i < iters; i += 1) { //iterating through the number of iters
	mpz_sub_ui(bound, n, 3); //setting the upper bound to be n - 3
        mpz_urandomm(a, state,
            bound); //this returns 0 to n - 1 (this is not inclusive, therefore it's n - 2)
        mpz_add_ui(a, a, 2); 
        pow_mod(y, a, r, n);
        if ((mpz_cmp_ui(y, 1) != 0)
            && (mpz_cmp(y, n_minus) != 0)) { // comparing if y != 1 and y != n-1

            mpz_set_ui(j, 1);

            while ((mpz_cmp_ui(j, s) <= 0) && (mpz_cmp(y, n_minus) != 0)) {
                pow_mod(y, y, two, n);
                if (mpz_cmp_ui(y, 1) == 0) {
                    // printf("not prime"); //testing
		     return false;
                }
                mpz_add_ui(j, j, 1);
            }
            if (mpz_cmp(y, n_minus) != 0) {
		//printf("not prime"); //testing
                return false;
            }

        }
    }
    mpz_clears(n_minus, r, two, a, bound, y, j, NULL); //no memory leak
    //printf("is prime"); //testing
    return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    do {
        mpz_urandomb(p, state, bits); //keep generating a random number when its not prime
    } while (!is_prime(p, iters));
}

void mod_inverse(mpz_t o, mpz_t a, mpz_t n) {
    mpz_t r, r1, t, t1, q, tempr, tempt; //initialize
    mpz_inits(r, r1, t, t1, q, tempr, tempt, NULL);

    //mpz_init(o);
    //mpz_init(a);
    //mpz_init(n);

    mpz_set(r, n); //(r,r′) ←(n,a)
    mpz_set(r1, a); 
    mpz_set_ui(t, 0); //(t,t′) ←(0,1)
    mpz_set_ui(t1, 1);
    while (mpz_cmp_ui(r1, 0) != 0) { //while r′ != 0
        //this is r and r1

        mpz_fdiv_q(q, r, r1);  //q ← r/r′
        mpz_set(tempr, r);    //(r,r′) ←(r′,r−q×r′)
        mpz_set(r, r1);		//(using a temp variable to not overwrite r)
        mpz_mul(r1, q, r1);
        mpz_sub(r1, tempr, r1);

        //this is t and t1
        mpz_set(tempt, t); //(t,t′) ←(t′,t−q×t′)
        mpz_set(t, t1);     //using a temp variable to not overwrite t 
        mpz_mul(t1, q, t1);
        mpz_sub(t1, tempt, t1);
    }
    if (mpz_cmp_ui(r, 1) > 0) { //if r > 1
        mpz_set_ui(o, 0);
        return;  //return no inverse
    }
    if (mpz_cmp_ui(t, 0) < 0) {
        mpz_add(t, t, n);
        //mpz_set(o,t);
    }
    mpz_set(o, t); //storing in outfile
    mpz_clears(r, r1, t, t1, q, tempr, tempt, NULL);
    return; //return o
}

void gcd(mpz_t g, mpz_t a, mpz_t b) {
    mpz_t t;
    mpz_init(t); //initialize (clear to me)

    //mpz_init(a);
    //mpz_init(g);
    //mpz_init(b);

    while (mpz_cmp_ui(b, 0) != 0) { //while b != 0
        mpz_set(t, b); // set b to t
        mpz_mod(b, a, b); //assign a % b to b
        mpz_set(a, t); // assign t to a
    }
    mpz_set(g, a); //setting a to g 
    mpz_clear(t); //clearing
}

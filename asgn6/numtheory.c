#include "numtheory.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>

//CITE: Professor Long (pseudo for number theory)
//CITE: TA Eugene (structure) (11/9 section)
//CITE: Tutor Miles (is_prime & make prime) (11/10 session)
//CITE: Tutor Eric (is_prime & make prime) (11/10 session)

void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n) {
    mpz_t v, p; //initialize v and p
    mpz_init_set_ui(v, 1); //initialize the set of v with 1
    mpz_init_set(p, a); //initialize the set with the base
    while (mpz_cmp_ui(d, 0) > 0) { //compare the exponent to be greater than 0
        if (1 == mpz_mod_ui(d, d, 2)) { //if the exponent is odd
	    mpz_mul(v, v, p); //do operation v = v x p
            mpz_mod(v, v, n); //and find the modulus of that
        }
        mpz_mul(p, p, p); //multiply the p with itself
        mpz_mod(p, p, n); //and assgn it to the modulus of n
        mpz_divexact_ui(d, d, 2); //divide d by 2
    }
    mpz_set(o, v); //store the computed result in out.
    mpz_clears(v,p, NULL); //no memory leak
}

bool is_prime(mpz_t n, uint64_t iters){
	mpz_t n_minus, r, two;
	mp_bitcount_t s = 2;
        mpz_inits(n_minus,r, two, NULL);
	mpz_sub_ui(n_minus, n, 1);
	mpz_set_ui(two, 2);
	mp_bitcount_ts = 2; //this is just a bit counter -- in 2^s 
	
	while(mps_divisible_2xp_p(n_minus, s)){//break until it is not divisible by 2
		s += 1;		
	}
	s -= 1;
	mpz_tdiv_q_2exp(r, n_minus, s)//storing it to r
	
	mpz_t a, bound, y, j, s_minus;//we need a bound because we want a to be between 2 to n - 1
	mpz_inits(a, bound, y,j, s_minus, NULL);
	for(i = 0; i < iters, i += 1){
		mpz_sub_ui(bound, n, 3);
		mpz_urandom(a,state, bound); //this returns 0 to n - 1 (this is not inclusive, therefore it's n - 2)
		mpz_add_ui(a, a, 2);
		pow_mod(y, a, r, n);
		mpz_sub_ui(s_minus, s, 1)
		if((mpz_cmp_ui(y, 1) != 0)) && (mpz_cmp(n_minus,y) != 0){
			
			mpz_set_ui(j, 1);
			
			while((mpz_cmp_ui(j, s_minus) <= 0) && (mpz_cmp(y, n_minus) != 0)){
				pow_mod(y, y, two, n);
				if(mpz_cmp_ui(y, 0) == 0){
					return false;
				}
				mpz_add_ui(j, j, 1);
			}
			if(mpz_cmp_ui(y, n_minus) != 0){
				return false;
			}

		}
	}
	return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters){
	do{
		mpz_urandom(p,state, bits);
	} while(!is_prime(p, iters));
}



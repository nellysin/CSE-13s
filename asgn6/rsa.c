#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>

#include "rsa.h"
#include "randstate.h"
#include "numtheory.h"

//CITE: Professor Long (assgn doc)
//CITE: TA Eugene (structure) (11/9 section)
//CITE: Tutor Eric (rsa_make_pub) (11/10 session)

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    mpz_t p_min, q_min, gcd_totient, totient; //initializing 
    mpz_inits(p_min, q_min, gcd_totient, totient, NULL);

    uint64_t pbits
        = (random() % ((3 * nbits / 4) - (nbits / 4) + 1)) //CITE: Tutor Jason
          + (nbits / 4); //calculating the num of bits we will be passing (asgn doc)

    printf("pbits: %lu\n", pbits);

    uint64_t qbits = nbits - pbits; // you cannot stop to a lower bound and end in upper bound

    printf("qbits: %lu\n", qbits);

    make_prime(q, qbits, iters); //generate a prime number for q
    make_prime(p, pbits, iters); //generate a prime number for p
    
    mpz_sub_ui(p_min, p, 1); //p_min = p - 1
    mpz_sub_ui(q_min, q, 1); //q_min = q - 1
    mpz_mul(totient, p_min, q_min); // the computed totient
    mpz_mul(n, p, q); // the product of p and q


    do {
        mpz_urandomb(e, state, nbits); //generate random numbers of around nbits using mpz_urandomb()
	gcd(gcd_totient, e, totient); //find the gcd of the random num and totient
    } while (mpz_cmp_ui(gcd_totient, 1) != 0);

    mpz_clears(p_min, q_min, gcd_totient, totient, NULL); //clearing the memory
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile); /*{
	gmp_vfprintf(pbfile, n, username[0]);
	gmp_vfprintf(pbfile, e, username[1]);
	gmp_vfprintf(pbfile, s, username[2]);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile){
	gmp_vscanf(pbfile, n, username[0]);
	gmp_vscanf(pbfile, e, username[1]);
	gmp_vscanf(pbfile, s, username[2]);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q){
	mpz_t totient, p_min, q_min;
	mpz_inits(totient, p_min, q_min, NULL);


	make_prime(p, e, iters); //generate a prime number for p
        make_prime(q, e, iters); //generate a prime number for q
	
	//compute d with the inverse of e modulo totient(n) = (p - 1)(q - 1)
	mpz_sub_ui(p_min, p, 1);
	mpz_sub_ui(q_min, q, 1);
	mpz_mul(totient, p_min, q_min);
	mod_inverse(d, e, totient) //public exponenet e 
	
	mpz_clears(totient, p_min, q_min, NULL);
}
void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile){
	gmp_fprintf(pvfile, n, d);
	gmp_fprintf(pvfile, n, d);
}
void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile);

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n);

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e);

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n);

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d);

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n);

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n);
*/
//the user name is passed in -- rsa pub
//getenv()
//$USER

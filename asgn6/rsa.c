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

    uint64_t pbits = (random() % ((3 * nbits / 4) - (nbits / 4) + 1)) //CITE: Tutor Jason
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
        mpz_urandomb(
            e, state, nbits); //generate random numbers of around nbits using mpz_urandomb()
        gcd(gcd_totient, e, totient); //find the gcd of the random num and totient
    } while (mpz_cmp_ui(gcd_totient, 1) != 0);

    mpz_clears(p_min, q_min, gcd_totient, totient, NULL); //clearing the memory
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n); //write to a public file
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);

    gmp_fprintf(pbfile, username);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n %Zx\n %Zx\n %Zs\n", n, e, s, username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    //compute the inverse of e modulo
    //totient(n) = (p-1)(q-1)
    mpz_t p_min, q_min, totient;
    mpz_inits(p_min, q_min, totient, NULL);

    mpz_sub_ui(p_min, p, 1);
    mpz_sub_ui(q_min, q, 1);
    mpz_mul(totient, p_min, q_min);
    mod_inverse(d, e, totient);

    mpz_clears(p_min, q_min, totient, NULL);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n); //write to a public file
    gmp_fprintf(pvfile, "%Zx\n", d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n %Zx\n", n, d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e);/* {
        mpz_t k, temp_n, div_eight, one, k_bytes; //calculate the block size k
        mpz_t inits(k, temp_n, c, div_eight,one,k_bytes, NULL);

        //k = floor((log_2 (n) - 1) - (1 / 8))
        mpz_set_ui(k, 0);
        mpz_set_ui(one, 1);
        mpz_set(temp_n, n);

        mpz_cdiv_q_ui(k, one, 8);

        //log_2 (n)
        while(temp_n > 0){
                mpz_add_ui(k, 1);
                mpz_fdiv_q_ui(temp_n, 2);
        }
        mpz_sub_ui(k, 1); // log_2(n) - 1

        mpz_sub(k, div_eight); // k - (1/8)

        uint8_t *k_bytes[k]; //dynamically allocate an array that can hold k bytes

        uint8_t k_bytes[0] = 0xFF; // setting the zeroth byte of the block to 0xFF

}*/

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n){
	pow_mod(m, c, d, n);
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d);

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n){
	pow_mod(s, m, d, n);
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);

    pow_mod(t, s, e, n);

    if (mpz_cmp(t, s) == 0) {
        return true;
    } else {
        return false;
    }

    mpz_clear(t);
}
//the user name is passed in -- rsa pub
//getenv()
//$USER

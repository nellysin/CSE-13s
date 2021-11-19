#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "rsa.h"
#include "randstate.h"
#include "numtheory.h"

//CITE: Professor Long (assgn doc)
//CITE: TA Eugene (structure encrypt_file & decrypt_file) (11/9 section)
//CITE: Tutor Eric (rsa_make_pub) (11/10 session)

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    mpz_t p_min, q_min, gcd_totient, totient; //initializing
    mpz_inits(p_min, q_min, gcd_totient, totient, NULL);

    do {
        uint64_t pbits = (random() % (nbits / 2)) + (nbits / 4);
        uint64_t qbits = nbits - pbits; // you cannot stop to a lower bound and end in upper bound
        make_prime(q, qbits, iters); //generate a prime number for q
        make_prime(p, pbits, iters); //generate a prime number for p
        mpz_mul(n, p, q); // the product of p and q
    } while (!(mpz_sizeinbase(n, 2) == nbits)); //until it equals to nbits

    mpz_sub_ui(p_min, p, 1); //p_min = p - 1
    mpz_sub_ui(q_min, q, 1); //q_min = q - 1
    mpz_mul(totient, p_min, q_min); // the computed totient

    do {
        mpz_urandomb(
            e, state, nbits); //generate random numbers of around nbits using mpz_urandomb()
        gcd(gcd_totient, e, totient); //find the gcd of the random num and totient
    } while (mpz_cmp_ui(gcd_totient, 1) != 0);

    mpz_clears(p_min, q_min, gcd_totient, totient, NULL); //clearing the memory
    return;
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n); //write to a public file
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);

    gmp_fprintf(pbfile, "%s\n", username);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n%Zx\n%Zx\n%s\n", n, e, s, username); //reading the public file
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t p_min, q_min, totient; //initialize
    mpz_inits(p_min, q_min, totient, NULL);

    mpz_sub_ui(p_min, p, 1); //p_min = p - 1
    mpz_sub_ui(q_min, q, 1); //q_min = q - 1
    mpz_mul(totient, p_min, q_min); //totient = p_min * qmin
    mod_inverse(d, e, totient); //mod inverse

    mpz_clears(p_min, q_min, totient, NULL); //clearing
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n); //write to a public file
    gmp_fprintf(pvfile, "%Zx\n", d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n %Zx\n", n, d); //reading in the file for private
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n); //call pow mod
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    mpz_t c, m; //initialize
    mpz_inits(c, m, NULL);
    size_t k; //setting k
    size_t j = 1; //setting j to 1

    k = (mpz_sizeinbase(n, 2) - 1); //k = log_2(n) //doing the mathematics equation
    k = (k / 8);

    uint8_t *blocke = (uint8_t *) calloc(k, sizeof(uint8_t)); //allocating block
    blocke[0] = 0xFF; //storing the 0th index to 0xFF

    while (j > 0) {
        j = fread(blocke + 1, sizeof(uint8_t), k - 1, infile); //passing fread to j
        mpz_import(m, j + 1, 1, sizeof(blocke[0]), 1, 0, blocke); //from assignment doc
        rsa_encrypt(c, m, e, n);
        gmp_fprintf(outfile, "%Zx\n", c); //printing to the outfile
    }

    mpz_clears(c, m, NULL); //free and clear for no memory leak
    free(blocke);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n); //call pow mod
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    mpz_t c, m; //initialize c and m
    mpz_inits(c, m, NULL);

    uint64_t k = 0; //set k and j
    uint64_t j = 1;

    k = (mpz_sizeinbase(n, 2) - 1) / 8; //k = log_2(n)

    uint8_t *blocke = (uint8_t *) calloc(k, sizeof(uint8_t));

    while ((j = gmp_fscanf(infile, "%Zx\n", c))
           != EOF) { //while fscanf is not end of file (similar to asgn 4)
        rsa_decrypt(m, c, d, n); //calling rsa_decrypt
        mpz_export(blocke, &j, 1, sizeof(blocke[0]), 1, 0, m); //from assignment doc
        fwrite(blocke + 1, sizeof(uint8_t), j - 1, outfile); //passing fread to j
    }

    mpz_clears(c, m, NULL); //clearing for no leakage
    free(blocke); //free for no leakage
    return;
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n); //call pow mod
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t; //follow assign doc
    mpz_init(t);

    pow_mod(t, s, e, n); //call pow mod

    if (mpz_cmp(t, m) == 0) { //if username and t is equal set to true else false
        mpz_clear(t);
        return true;
    } else {
        mpz_clear(t); //clearing
        return false;
    }
}

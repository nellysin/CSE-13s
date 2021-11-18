#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#define OPTIONS "hvb:c:n:d:s:"

//CITE: Professor Long (assign doc)
//CITE: TA Eugene for files & vebosing (11/16 session)

gmp_randstate_t state;

void menu(void) { //printing out the menu
    printf("SYNOPSIS\n");
    printf("   Generates an RSA public/private key pair.\n");
    printf("\n");
    printf("USAGE\n");
    printf("   ./keygen [-hv] [-b bits] -n pbfile -d pvfile\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("   -h              Display program help and usage.\n");
    printf("   -v	           Display verbose program output.\n");
    printf("   -b bits         Minimum bits needed for public key n (default: 256).\n");
    printf("   -i confidence   Miller-Rabin iterations for testing primes (default: 50).\n");
    printf("   -n pbfile       Public key file (default: rsa.pub).\n");
    printf("   -d pvfile       Private key file (default: rsa.priv).\n");
    printf("   -s seed         Random seed for testing.\n");
    return;
}

int main(int argc, char **argv) {
    FILE *pubfile = stdout; //pubfile set to stdout
    FILE *privfile = stdout; //privfile set to stdout

    bool stdpub = false; //this is to set to default or not
    bool stdpriv = false; //set to default or not

    // privpath = "rsa.pub";

    bool verbose = false; //setting verbose printing

    uint64_t bits = 256; //setting the minimum bits
    uint64_t itersMR = 50; //setting the default iterations
    uint64_t seed = time(NULL); //setting the seed to time

    int opt = 0; //this is opt targs
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) { //switch cases for each
        case 'h':
            menu(); //help menu
            return 0;
        case 'v':
            verbose = true; //for verbose printing
            break;
        case 'b':
            bits = atoi(optarg); //minimum bits if 256
            break;
        case 'c':
            itersMR = atoi(optarg); //amount of iterattions for MR
            break;
        case 'n':
            stdpub = true; //setting the stdpub to true (setting the file name to optarg)
            pubfile = fopen(optarg, "w");
            if (!pubfile) {
                fprintf(stderr, "Error: unable to write file.\n"); //error if pubfile does not exist
                fclose(pubfile);
                fclose(privfile);
                return 0;
            }
            break;
        case 'd':
            stdpriv = true; //setting the stdpriv as true (set the file name to optarg)
            privfile = fopen(optarg, "w"); //error if the privfile does not exist
            if (!privfile) { //if the privfile does not exist
                fprintf(stderr, "Error: unable to write file.\n");
                fclose(privfile);
                fclose(pubfile);
                return 0;
            }
            break;
        case 's':
            seed = atoi(optarg); //set the seed to what the user inputs
            break;
        default:
            menu(); //else call the menu again
            return 0;
        }
    }

    int pvkey = fileno(privfile); //permission files
    fchmod(pvkey, 0600);

    mpz_t p, q, n, e, d, s, m; //initilizing P Q N E D (steps 4 - 6 asgn doc)
    mpz_inits(p, q, n, e, d, s, m, NULL);

    randstate_init(seed); //initialize random state (4)

    rsa_make_pub(p, q, n, e, bits, itersMR); //rsa make pub and priv (5)
    rsa_make_priv(d, e, p, q);

    char *user[sizeof(getenv("USER"))]; //get user's name as string (6)
    *user = getenv("USER");

    mpz_set_str(m, *user, 62); //specified in the assignment doc
    rsa_sign(s, m, d, n); //call rsa sign

    if (stdpub == false) { //writing to the rsa.pub
        pubfile = fopen("rsa.pub", "w");
        if (!pubfile) { //if this file does not exist
            fprintf(stderr, "Error: unable to write file.\n");
            fclose(pubfile);
            fclose(privfile);
            randstate_clear();
            mpz_clears(p, q, n, e, d, s, m, NULL);
            return 0;
        }
    }

    if (stdpriv == false) { //writing to the rsa.priv
        privfile = fopen("rsa.priv", "w");
        if (!privfile) { //if this file does not exist
            fprintf(stderr, "Error: unable to write file.\n");
            fclose(pubfile);
            fclose(privfile);
            randstate_clear();
            mpz_clears(p, q, n, e, d, s, m, NULL);
            return 0;
        }
    }

    rsa_write_pub(n, e, s, *user, pubfile); //writing to the pubfile
    rsa_write_priv(n, d, privfile); //writing to the privfile

    size_t pribits; //where to store the bits

    if (verbose == true) { //if verbose is true
        gmp_fprintf(stdout, "user = %s\n", *user);

        pribits = mpz_sizeinbase(s, 2);
        gmp_fprintf(stdout, "s (%zu bits) = %Zd\n", pribits, s);

        pribits = mpz_sizeinbase(p, 2);
        gmp_fprintf(stdout, "p (%zu bits) = %Zd\n", pribits, p);

        pribits = mpz_sizeinbase(q, 2);
        gmp_fprintf(stdout, "q (%zu bits) = %Zd\n", pribits, q);

        pribits = mpz_sizeinbase(n, 2);
        gmp_fprintf(stdout, "n (%zu bits) = %Zd\n", pribits, n);

        pribits = mpz_sizeinbase(e, 2);
        gmp_fprintf(stdout, "e (%zu bits) = %Zd\n", pribits, e);

        pribits = mpz_sizeinbase(d, 2);
        gmp_fprintf(stdout, "d (%zu bits) = %Zd\n", pribits, d);
    }

    randstate_clear();
    mpz_clears(p, q, n, e, d, s, m, NULL);
    fclose(privfile);
    fclose(pubfile);
    return 0;
}

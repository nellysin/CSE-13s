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
#include <limits.h>

#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#define OPTIONS "i:o:n:vh"

//CITE: Professor Long
//CITE: TA Eugene making files
//CITE: TA Sloan (size of the user array)

void menu(void) {
    printf("SYNOPSIS\n");
    printf("   Encrypts data using RSA encryption.\n");
    printf("   Encrypted data is decrypted by the decrypt program.\n");
    printf("\n");
    printf("USAGE\n");
    printf("   ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("   -h              Display program help and usage.\n");
    printf("   -v              Display verbose program output.\n");
    printf("   -i infile       Input file of data to encrypt (default: stdin).\n");
    printf("   -o outfile      Output file for encrypted data (default: stdout).\n");
    printf("   -n pbfile       Public key file (default: rsa.pub).\n");
    return;
}

int main(int argc, char **argv) {
    FILE *inpub = stdin;
    FILE *outpub = stdout;
    FILE *pubkey = stdin;

    bool pub = false;
    bool verbose = false;

    int opt = 0; //the following are command lines
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) { //switch cases for each
        case 'h':
            menu(); //help menu
            return 0;
        case 'v':
            verbose = true; //for verbose printing
            break;
        case 'n':
            pub = true; //setting the stdpub to true (setting the file name to optarg)
            pubkey = fopen(optarg, "r");
            if (!pubkey) {
                fprintf(stderr, "Error: unable to read file.\n"); //error if pubfile does not exist
                fclose(inpub);
                fclose(outpub);
                fclose(pubkey);
                return 0;
            }
            break;
        case 'i':
            inpub = fopen(optarg, "r");
            if (!inpub) {
                fprintf(stderr, "Error: unable to read file.\n");
                fclose(outpub);
                fclose(pubkey);
                return 0;
            }
            break;
        case 'o':
            outpub = fopen(optarg, "w");
            if (!outpub) {
                fprintf(stderr, "Error: unable to write file.\n");
                fclose(inpub);
                fclose(pubkey);
                return 0;
            }
            break;
        default:
            menu(); //else call the menu again
            return 0;
        }
    }

    mpz_t n, e, s, m; //initialize
    mpz_inits(n, e, s, m, NULL);

    //read the public key from the opened public key file

    if (pub == false) { //writing to the rsa.pub
        pubkey = fopen("rsa.pub", "r");
        if (!pubkey) {
            fprintf(stderr, "Error: unable to read public key.\n");
            fclose(inpub);
            fclose(outpub);
            return 0;
        }
    }

    char user[256]; //define username for reading

    rsa_read_pub(n, e, s, user, pubkey); //reading public key

    mpz_set_str(m, user, 62); //specified in the assignment doc

    if (!rsa_verify(m, s, e, n)) {
        fprintf(stderr, "Signature not verified.\n");
        mpz_clears(n, e, s, m, NULL);
        fclose(inpub);
        fclose(outpub);
        fclose(pubkey);
        return 0;
    }

    size_t pribits; //where to store the bits
    //verbose is true
    if (verbose == true) {
        gmp_fprintf(stdout, "user = %s\n", user);

        pribits = mpz_sizeinbase(s, 2);
        gmp_fprintf(stdout, "s (%zu bits) = %Zd\n", pribits, s);

        pribits = mpz_sizeinbase(n, 2);
        gmp_fprintf(stdout, "n (%zu bits) = %Zd\n", pribits, n);

        pribits = mpz_sizeinbase(e, 2);
        gmp_fprintf(stdout, "e (%zu bits) = %Zd\n", pribits, e);
    }
    
    rsa_encrypt_file(inpub, outpub, n, e); //rsa encrypt file

    mpz_clears(n, e, s, m, NULL);
    fclose(inpub);
    fclose(outpub);
    fclose(pubkey);
    return 0;
}

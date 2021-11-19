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

//CITE: Professor Long for assignment doc
//CITE: TA Eugene for opening files
//CITE: TA Sloan (size of the user array)

void menu(void) { //helper function
    printf("SYNOPSIS\n");
    printf("   Decrypts data using RSA decryption.\n");
    printf("   Encrypted data is encrypted by the encrypt program.\n");
    printf("\n");
    printf("USAGE\n");
    printf("   ./decrypt [-hv] [-i infile] [-o outfile] -n privkey\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("   -h              Display program help and usage.\n");
    printf("   -v              Display verbose program output.\n");
    printf("   -i infile       Input file of data to encrypt (default: stdin).\n");
    printf("   -o outfile      Output file for encrypted data (default: stdout).\n");
    printf("   -n pvfile       Private key file (default: rsa.priv).\n");
    return;
}

int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdin;
    FILE *privkey = stdin;

    bool priv = false; //for boolean
    bool verbose = false; //for verbose

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
            priv = true; //setting the stdpub to true (setting the file name to optarg)
            privkey = fopen(optarg, "r");
            if (!privkey) {
                fprintf(stderr, "Error: unable to read file.\n"); //error if pubfile does not exist
                fclose(infile);
                fclose(outfile);
                fclose(privkey);
                return 0;
            }
            break;
        case 'i': //this is for infile
            infile = fopen(optarg, "r");
            if (!infile) {
                fprintf(stderr, "Error: unable to read file.\n");
                fclose(infile);
                fclose(outfile);
                fclose(privkey);
                return 0;
            }
            break;
        case 'o': //this is for outfile
            outfile = fopen(optarg, "w");
            if (!outfile) {
                fprintf(stderr, "Error: unable to write file.\n");
                fclose(infile);
                fclose(outfile);
                fclose(privkey);
                return 0;
            }
            break;
        default:
            menu(); //else call the menu again
            return 0;
        }
    }

    mpz_t n, s, d; //initialize
    mpz_inits(n, s, d, NULL);

    //read the public key from the opened public key file

    if (priv == false) { //writing to the rsa.pub
        privkey = fopen("rsa.priv", "r"); //if it doesn't exist then print error and exit
        if (!privkey) {
            fprintf(stderr, "Error: unable to write file.\n");
            fclose(infile);
            fclose(outfile);
            fclose(privkey);
            return 0;
        }
    }

    rsa_read_priv(n, d, privkey);

    size_t pribits; //where to store the bits

    //verbose is true
    if (verbose == true) {
        pribits = mpz_sizeinbase(n, 2); //printing the bits
        gmp_fprintf(stdout, "n (%zu bits) = %Zd\n", pribits, n); //printing out n

        pribits = mpz_sizeinbase(d, 2); //printing out the bits
        gmp_fprintf(stdout, "d (%zu bits) = %Zd\n", pribits, d); //printing out d
    }

    rsa_decrypt_file(infile, outfile, n, d);

    mpz_clears(n, s, d, NULL); //clear and close for no memory leaks
    fclose(infile);
    fclose(outfile);
    fclose(privkey);
    return 0;
}

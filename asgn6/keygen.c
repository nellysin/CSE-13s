#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/stat.h>

#include <gmp.h>

#include "numtheory.h"
#include "randstate.h"

#define SET 0600
#define OPTIONS

void menu(void) {
    printf("SYNOPSIS\n");
    printf("   Generates an RSA public/private key pair.\n");
    printf("\n");
    printf("USAGE\n");
    printf("   ./keygen [-hv] [-b bits] -n pbfile -d pvfile\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("   -h              Display program help and usage.\n");
    printf("   -v		   Display verbose program output.\n");
    printf("   -b bits         Minimum bits needed for public key n.\n");
    printf("   -c confidence   Miller-Rabin iterations for testing primes (default: 50).\n");
    printf("   -n pbfile       Public key file (default: rsa.pub).\n");
    printf("   -d pvfile       Private key file (default: rsa.priv).\n");
    printf("   -s seed         Random seed for testing.\n");
}

int main(void) {
    //    int pbfile = STDOUT_FILENO;
    //    if (pbfile != STDOUT_FILENO) {
    //        close(pbfile);
    //    }

    //    int pvfile = STDOUT_FILENO;
    //    if (pvfile != STDOUT_FILENO) {
    //        close(pvfile);
    //    }

    //    fchmod(pbfile, set);
    //    fchmod(pvfile, set);

    //    randstate_init(SET);

    //    rsa_make_pub();

    return 0;
}

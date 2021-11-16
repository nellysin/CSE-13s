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

void menu(void) {
    printf("SYNOPSIS\n");
    printf("   Generates an RSA public/private key pair.\n");
    printf("\n");
    printf("USAGE\n");
    printf("   ./keygen [-hv] [-b bits] -n pbfile -d pvfile\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("   -h              Display program help and usage.\n");
    printf("   -v	       Display verbose program output.\n");
    printf("   -b bits         Minimum bits needed for public key n.\n");
    printf("   -c confidence   Miller-Rabin iterations for testing primes (default: 50).\n");
    printf("   -n pbfile       Public key file (default: rsa.pub).\n");
    printf("   -d pvfile       Private key file (default: rsa.priv).\n");
    printf("   -s seed         Random seed for testing.\n");
    return;
}

int main(int argc, char **argv) {
	FILE *pubfile = stdout;
	FILE *privfile = stdout;

	bool stdpub = true;
	bool stdpriv = true;

	bool verbose = false;

	uint64_t bits = 256;
	uint64_t itersMR = 50;
	uint64_t seed = time(NULL);
	
	int opt = 0;
	while((opt = getopt(argc, argv, OPTIONS)) != -1){
		switch (opt){
			case 'h':
				menu();
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
				stdpub = false;
				pubfile = fopen(optarg, "w");
				if(!pubfile){
					fprintf(stderr, "Error: unable to write file.\n");
					fclose(pubfile);
					fclose(privfile);
					return 0;
				}
				break;
			case 'd':
				stdpriv = false;
				privfile = fopen(optarg, "w");
				if(!privfile){
					fprintf(stderr, "Error: unable to write file.\n");
					fclose(pubfile);
					fclose(privfile);
					return 0;
				}
				break;
			case 's':
				seed = atoi(optarg);
				break;
			default:
				menu();
				return 0;
		}
	}
	
	int pvkey = fileno(privfile);
	fchmod(pvkey, 0600);

	mpz_t p, q, n, e, d; //d = priv
	mpz_inits(p, q, n ,e, d, NULL);

        randstate_init(seed); //initialize random state (4)

        rsa_make_pub(p, q, n, e, bits, itersMR); //rsa make pub and priv (5)
	rsa_make_priv(d, e, p, q);

	char *user[sizeof(getenv("USER"))]; //get user's name as string (6)
	*user = getenv("USER");

	mpz_t m; //setting username to an mpz_t with mpz_set_str() (7)
	mpz_init(m);
	mpz_set_str(m, *user, 0);

	mpz_t s;   //using rsa_sign (7)
	mpz_init(s);
	rsa_sign(s, m, d, n);

	if(stdpub == true){ //writing to the rsa.pub 
                pubfile = fopen("rsa.pub", "w");
			if(!pubfile){
				fprintf(stderr, "Error: unable to write file.\n");
                        	fclose(pubfile);
                        	fclose(privfile);
				mpz_clears(p,q,n,e,d,s,m,NULL);
				randstate_clear();
				return 0;
			}
	}
	
	if(stdpriv == true){ //writing to the rsa.priv
		privfile = fopen("rsa.priv", "w");
		if(!privfile){
			fprintf(stderr, "Error: unable to write file.\n");
			fclose(pubfile);
			fclose(privfile);
			mpz_clears(p,q,n,e,d,s,m,NULL);
                        randstate_clear();
			return 0;
		}
	}

	rsa_write_pub(n, e, s, *user, pubfile);
	rsa_write_priv(n, d, privfile);

	if(verbose == true){ //if verbose is true
                printf("user = %s\n", *user);
                gmp_printf("s (%Zd bits) = %Zd", bits, itersMR);
                gmp_printf("p (%Zd bits) = %Zd", bits, p);
                gmp_printf("q (%Zd bits) = %Zd", bits, q);
                gmp_printf("n (%Zd bits) = %Zd", bits, n);
                gmp_printf("e (%Zd bits) = %Zd", bits, e);
                gmp_printf("d (%Zd bits) = %Zd", bits, d);
        }

    mpz_clears(p, q, n, e, d, m, s, NULL);
    randstate_clear();
    fclose(privfile);
    fclose(pubfile);
    return 0;
}

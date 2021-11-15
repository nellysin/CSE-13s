#include "randstate.h"

#include <stdint.h>
#include <gmp.h>

//CITE: Professor Long in assignment doc

gmp_randstate_t state; //global variable

void randstate_init(uint64_t seed) {
    gmp_randinit_mt(state); //initialize state
    gmp_randseed_ui(state, seed); //set seed to state
}

void randstate_clear(void) {
    gmp_randclear(state); //no memory leak
}

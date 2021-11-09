#include "randstate.h"

#include <stdint.h>
#include <gmp.h>

void randstate_init(uint64_t seed){
	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randinit_ui(state, seed);
}

void randstate_clear(void){
	gmp_randclear(state);
}

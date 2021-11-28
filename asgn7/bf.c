#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "bv.h"
#include "salts.h"
#include "speck.h"
#include "bf.h"

//CITE: Professor Long for the struct
//CITE: TA Eugene for asgn doc
//CITE: Tutor Jason for explanation for the hashing and bloom filter

struct BloomFilter { //struct for bloom filter (from the assignment doc)
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf;
    bf = (BloomFilter *) calloc(1, sizeof(BloomFilter)); //calloc the bf

    bf->filter = bv_create(size);

    bf->primary[0] = SALT_PRIMARY_LO; // setting primary, secondary, tertiary
    bf->primary[1] = SALT_PRIMARY_HI; // setting primary, secondary, tertiary

    bf->secondary[0] = SALT_SECONDARY_LO;
    bf->secondary[1] = SALT_SECONDARY_HI;

    bf->tertiary[0] = SALT_TERTIARY_LO;
    bf->tertiary[1] = SALT_TERTIARY_HI;

    return bf;
}
void bf_delete(BloomFilter **bf) {
    if (*bf && (*bf)->filter) {
        bv_delete(&(*bf)->filter);
        free(*bf); //free bf and filter for no memory leaks
        *bf = NULL;
    }
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(
        bf->filter); //return the length of the bloomfilter w/ the bitvector length function
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint32_t hashprim = hash(bf->primary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, hashprim);

    uint32_t hashsec = hash(bf->secondary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, hashsec);

    uint32_t hashter = hash(bf->tertiary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, hashter);
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t hashprim = hash(bf->primary, oldspeak);
    hashprim = hashprim % bf_size(bf);
    //return bv_get_bit(bf->filter, hashprim);

    uint32_t hashsec = hash(bf->secondary, oldspeak);
    hashsec = hashsec % bf_size(bf);
    //return bv_get_bit(bf->filter, hashsec);

    uint32_t hashter = hash(bf->tertiary, oldspeak);
    hashter = hashter % bf_size(bf);
    //return bv_get_bit(bf->filter, hashter);

    if (bv_get_bit(bf->filter, hashter) & bv_get_bit(bf->filter, hashsec)
        & bv_get_bit(bf->filter, hashprim)) {
        return true; //must return true if ALL are one
    } else {
        return false; //return false otherwise
    }
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bf_size(bf); i += 1) { //for i in the rnage of bf_size
        if (bv_get_bit(bf->filter, i) == 1) { //if the bf get bit if not 0 then increment count
            count += 1;
        }
    }
    return count; //returning the count
}

void bf_print(BloomFilter *bf); /*{
	for(uint32_t i = 0; i < bf_size(bf); i += 1){
		if()
	}
}*/

#include <stdbool.h>
#include <stdint.h>

#include "bv.h"

//CITE: Professor Long for code comments repo in bv8

struct BitVector{
	uint32_t length;
	uint8_t *vector;
};

BitVector *bv_create(uint32_t length){
	BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
	if(*bv){
		uint32_t bytes = (length / 8) + (length / 8 ? 1 : 0);
		bv->vector = (uint8_t *) calloc(bytes, sizeof(uint8_t));
		bv->length = length;
		return bv;
	} else {
		return (BitVector *) 0;
	}
}

void bv_delete(BitVector **bv){
	if(*bv){
		free(*bv);
		*bv = NULL;
	}
	return;
}

uint32_t bv_length(BitVector *bv){
	return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i){
	bv->vector[i / 8] |= (0x1 << i % 8);
}
bool bv_clr_bit(BitVector *bv, uint32_t i){
	bv->vector[i / 8] &= ~(0x1 << i % 8);
}

bool bv_get_bit(BitVector *bv, uint32_t i){
	bv->vector[i / 8] &= ~(0x1 >> i % 8) & 0x1;
}

void bv_print(BitVector *bv);

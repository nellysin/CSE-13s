#include "stats.h"
#include <stdio.h>
#include <stdlib.h>

int cmp(Stats *stats, uint32_t x, uint32_t y){
	if(x < y){
		return -1;
	}
	if(x == y){
		return 0;
	}
	if(x > y){
		return 1;
	}
}

uint32_t move(Stats *stats, uint32_t x){
 
}

void swap(Stats *stats, uint32_t *x, uint32_t *y){
}

void reset(Stats *stats){
}

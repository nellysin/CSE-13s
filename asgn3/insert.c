#include "insert.h"
#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define SEED 13371453
#define LENGTH 100
#define PRINT 100

//CITED: Professor Long for insertion sort sudo code
//CITED: Eugene Chou

void insertion_sort(Stats *stats,uint32_t *A, uint32_t n){
	for(uint32_t i = 1; i <= n; i += 1){ //loop that goes through the array
		int j = i; //j takes in whatever i is
		uint32_t temp = move(stats, A[i]); //store array[i] (element) to temp
		while(j > 0 && cmp(stats, A[j-1], temp) > 0){	//check if previous is < whatever is in A[j - 1] (previous) 
			A[j] = move(stats, A[j - 1]); 
			j -=1; //going all the past elements
		}
		A[j] = move(stats, temp); //place whatever temp is to array[j] as an element
	}
		return; //return the element in the array
}

/*int main(void){
	Stats stats;
	stats.moves= 0;
	stats.compares = 0;

	srandom(SEED);
	// Array of 100 uint32_t's
	uint32_t *A = (uint32_t *)calloc(LENGTH, sizeof(uint32_t));
	for(uint32_t i = 0; i <= LENGTH; i += 1){
		A[i] = random(); //remember to apply bitmask so each number is in 30-bits
	}

	insertion_sort(&stats, A, 100);

	printf("[");
	for (uint32_t i = 0; i < 100; i += 1) {
		printf("%" PRIu32, A[i]);
		if(i+1 != 100){
			printf(", \n");
		}
	}
	printf("]\n");

	printf("elements = %d\n",  LENGTH);
	printf("moves = %" PRIu64 "\n", stats.moves);
	printf("compares = %" PRIu64 "\n", stats.compares);

	reset(&stats);
	free(A);
}*/

#include "shell.h"
#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEED 13371453
#define LENGTH 100
#define PRINT 100

/* gap is how much between the numbers to compare
 * compare through out
 * decresing gap size will ensure the sorting in shell
 * at the end the gap will be 1, --> becoming insertion sort and looking backwards */
/* the value of our assignment: starts big and decreases:
 * 	switch when this is larger 
 * 	yield is the gap -- get a new gap based in the for loop with log*/
//CITE: Professor Long for Shell sudo code

void shell_sort(Stats *stats, uint32_t *A, uint32_t n){
	uint32_t max_gap = (log(3 + 2 * n)/ log(3));
	for(uint32_t gap = max_gap; gap > 0 ; gap -= 1){
		uint32_t yield = floor((pow(3, gap) - 1) / 2);
//		printf("%" PRIu32, yield);
		for(uint32_t i = yield; i <= n; i += yield){
			uint32_t j = i;
			uint32_t temp = A[i];
			while(j >= yield && temp < A[j - yield]){
				A[j] = move(stats, A[j - yield]);
				j -= yield;
			}
			A[j] = move(stats,temp);
		}
	}
	return;
}

int main(void){
        Stats stats;
        stats.moves= 0;
        stats.compares = 0;

        srandom(SEED);
        // Array of 100 uint32_t's
        uint32_t *A = (uint32_t *)calloc(LENGTH, sizeof(uint32_t));
	for(uint32_t i = 0; i <= LENGTH; i += 1){
                A[i] = random(); //remember to apply bitmask so each number is in 30-bits
        }

        shell_sort(&stats, A, 100);

        printf("[");
        for (uint32_t i = 0; i < 100; i += 1) {
                printf("%" PRIu32, A[i]);
                if(i+1 != 100){
                        printf("\n");
                }
        }
        printf("]\n");

        printf("elements = %d\n",  LENGTH);
        printf("moves = %" PRIu64 "\n", stats.moves);
        printf("compares = %" PRIu64 "\n", stats.compares);

        reset(&stats);
        free(A);

	return 0;
}


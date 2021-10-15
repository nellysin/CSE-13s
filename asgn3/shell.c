#include "shell.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>

/* gap is how much between the numbers to compare
 * compare through out
 * decresing gap size will ensure the sorting in shell
 * at the end the gap will be 1, --> becoming insertion sort and looking backwards */
/* the value of our assignment: starts big and decreases:
 * 	switch when this is larger 
 * 	yield is the gap -- get a new gap based in the for loop with log*/
//CITE: Professor Long for Shell sudo code
//CITE: Eugene Chou for idea structure during section

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t max_gap = (log(3 + 2 * n) / log(3)); //taking in the max gap first
    for (uint32_t gap = max_gap; gap > 0;
         gap -= 1) { //gap takes in max gap and de-increment until it reaches 1
        uint32_t yield = floor((pow(3, gap) - 1) / 2); // this will be the gap
        for (uint32_t i = yield; i <= n;
             i += yield) { // this is setting the gap and iterating through the array (index)
            uint32_t j = i; //j takes in i for temp
            uint32_t temp;
            move(stats, temp = A[i]); // temp takes
            while (j >= yield && cmp(stats, temp, A[j - yield]) < 0) {
                move(stats, A[j] = A[j - yield]);
                j -= yield;
            }
            move(stats, A[j] = temp);
        }
    }
    return;
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
}*/

#include "quick.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

/* do a for loop that goes through each element in the array
 * the pivot will be last element of the array (A[n])
 * while j is 0 and i is j - 1 (these will be the ones swapping the actual element)
 * if A[pivot] is > A[j], A[j] will swap with A[i - 1]
 * Partition: is when j = n
 * 	"i" will continue through the look and i + 1 is the partition
 */

//CITE: Professor Long for sudo code
//CITE: TA Eugene for explaination
//CITE: Tutor Miles for explaination for uint63_t

uint64_t partition(Stats *stats, uint32_t *A, uint64_t lo, uint64_t hi){ // this is partition helper function
	uint32_t i = lo - 1; // set i

	for(uint32_t j = lo; j < hi; j += 1){ // j is going through thr range of A
		if(cmp(stats, A[j - 1], A[hi - 1]) < 0){ //comparing if pivot is higher
			i += 1; // i will be the one that is swapping
			swap(stats, &A[i -1], &A[j - 1]); //swapping j and i if it's true
		}
	}
	swap(stats, &A[i], &A[hi -1]); // make partition
	return(i + 1);
}

uint32_t sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi){ //sorting helper function
	if(lo < hi){
		uint64_t p = partition(stats, A, lo, hi); //calling partition function
		sorter(stats, A, lo, p - 1);	//recursion 
		sorter(stats, A, p + 1, hi);   //recursion 
	}
	return 0;
}

void quick_sort(Stats *stats, uint32_t *A, uint32_t n){ //the actual qucik sort that calls the helper functions

	sorter(stats, A, 1, n);

	return;
}

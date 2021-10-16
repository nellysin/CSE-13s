
#include "heap.h"

#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* heap sort = save my current array and fix the heap (using a tree)
 * parent will always be larger
 * the largest will be taken out in the array
*/

//CITE: Professor Long for sudo code
//CITE: TA Eugene for how it works

uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first,
    uint32_t last) { // max_child is finding the maximim of parents children
    uint32_t left
        = 2 * first; // the left side (this will set the current element of left and right side)
    uint32_t right = left + 1; // the right side
    if (right <= last
        && cmp(stats, A[right - 1], A[left - 1])
               > 0) { // comparing right and left elements (the actual comparting)
        return right;
    }
    return left;
}

uint32_t fix_heap(Stats *stats, uint32_t *A, uint32_t first,
    uint32_t last) { // fix heap is the sorting of the array
    bool found = false;
    uint32_t mother = first;
    uint32_t great = max_child(stats, A, mother, last);

    while (mother <= floor(last / 2) && (found == false)) {
        if (cmp(stats, A[mother - 1], A[great - 1])
            < 0) { //the largest element will be removed from the top
            swap(stats, &A[mother - 1], &A[great - 1]); // it ends up on the end of the sorted array
            mother = great; // then the heap must be fixed again by going back to max_child
            great = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }
    return 0;
}

uint32_t build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t father = floor(last / 2); father > (first - 1); father -= 1) {
        fix_heap(stats, A, father, last);
    }
    return 0;
}

void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    build_heap(stats, A, first, n);
    for (uint32_t leaf = n; leaf > first; leaf -= 1) {
        swap(stats, &A[first - 1], &A[leaf - 1]);
        fix_heap(stats, A, first, leaf - 1);
    }
    return;
}

int main(void) {
    uint32_t SEED = 13371453;
    uint32_t ELEM = 100;
    uint32_t PR = 100;

    Stats stats;
    stats.moves = 0;
    stats.compares = 0;

    srandom(SEED);
    uint32_t mask = 0x3fffffff;
    // Array of 100 uint32_t's
    uint32_t *A = (uint32_t *) malloc(sizeof(uint32_t) * ELEM);
    for (uint32_t i = 0; i < ELEM; i += 1) {
        A[i] = random() & mask; //remember to apply bitmask so each number is in 30-bits
    }

    heap_sort(&stats, A, ELEM);

    printf(" %" PRIu32 " elements ", ELEM);
    printf("%" PRIu64 " moves", stats.moves);
    printf(" %" PRIu64 " compares\n", stats.compares);
    for (uint32_t i = 0; i < PR && i < ELEM; i += 1) {
        if (i % 5 == 0 && i != 0) {
            printf("\n");
        }
        printf("%13" PRIu32, A[i]);
    }
    printf("\n");

    reset(&stats);
    free(A);

    return 0;
}

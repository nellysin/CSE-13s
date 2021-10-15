/* heap sort = save my current array and fix the heap (using a tree)
 * parent will always be larger
 * the largest will be taken out in the array
*/
#include "heap.h"

#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SEED   13371453
#define LENGTH 100
#define PRINT  100

void max_child(Stats *stats, *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * root;
    uint32_t right = (2 * root) + 1;

    if (right <= last && A[right - 1] > A[left - 1]) {
        return right;
    } else {
        return left;
    }
}

void fix_heap(Stats *stats, A, uint32_t first, uint32_t last) {
    bool found = false;
    mother = first great = max_sort(&stats, A, mother, last);

    while (mother <= floor(n / 2) && found == false) {
        if (A[mother - 1] < A[great - 1]) {
            A[mother - 1], A[great - 1] = A[great - 1], A[mother - 1];
            mother = great;
            great = max_sort(&stats, A, n);
        }
    }
    else {
        found = true;
    }
    return;
}

void build_heap(Stats *stats, A, uint32_t first, uint32_t last) {
    for (uint32_t father = floor(last / 2); father > first - 1; father -= 1;) {
        fix_heap(&stats; A, father, last);
    }
    return;
}

void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(&stats, A, first, last);

    for (uint32_t leaf = n; leaf >= first; leaf -= 1) {
        A[first - 1] = A[leaf - 1];
        A[leaf - 1] = A[first - 1];
        build_heap(&stats, A, leaf - 1);
    }
    return;
}

int main(void) {
    Stats stats;
    stats.moves = 0;
    stats.compares = 0;

    srandom(SEED);
    uint32_t mask = 0x3fffffff;
    // Array of 100 uint32_t's
    uint32_t *A = (uint32_t *) calloc(LENGTH, sizeof(uint32_t));
    for (uint32_t i = 0; i < LENGTH; i += 1) {
        A[i] = random() & mask; //remember to apply bitmask so each number is in 30-bits
    }

    heap_sort(&stats, A, 100);

    printf("[");
    for (uint32_t i = 0; i < 100; i += 1) {
        printf("%" PRIu32, A[i]);
        if (i + 1 != 100) {
            printf(", \n");
        }
    }
    printf("]\n");

    printf("elements = %d\n", LENGTH);
    printf("moves = %" PRIu64 "\n", stats.moves);
    printf("compares = %" PRIu64 "\n", stats.compares);

    reset(&stats);
    free(A);

    return 0;
}

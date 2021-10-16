
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

uint32_t build_heap(Stats *stats, uint32_t *A, uint32_t first,
    uint32_t last) { //this is the first helper function heap_sort takes
    for (uint32_t father = floor(last / 2); father > (first - 1);
         father -= 1) { //ordering the elements by the largest element
        fix_heap(stats, A, father, last);
    }
    return 0;
}

void heap_sort(Stats *stats, uint32_t *A,
    uint32_t n) { // this is the main heap_sort where it connects all the helper functions
    uint32_t first = 1;
    build_heap(stats, A, first, n);
    for (uint32_t leaf = n; leaf > first;
         leaf -= 1) { //where the elements swap if they have found the largest (fix_heap)
        swap(stats, &A[first - 1], &A[leaf - 1]);
        fix_heap(stats, A, first, leaf - 1);
    }
    return;
}

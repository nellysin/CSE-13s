#include "insert.h"

#include <stdio.h>

//CITED: Professor Long for insertion sort sudo code
//CITED: Eugene Chou

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t temp;
    for (uint32_t i = 1; i < n; i += 1) { //loop that goes through the array
        int j = i; //j takes in whatever i is
        move(stats, temp = A[i]); //store array[i] (element) to temp
        while (j > 0
               && cmp(stats, temp, A[j - 1])
                      < 0) { //check if previous is < whatever is in A[j - 1] (previous)
            move(stats, A[j] = A[j - 1]);
            j -= 1; //going all the past elements
        }
        move(stats, A[j] = temp); //place whatever temp is to array[j] as an element
    }
    return; //return the element in the array
}

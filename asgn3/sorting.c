#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "haeisqn:p:r:"

typedef enum { HEAP, SHELL, INSERTION, QUICK } Sorts;

// CITE: Professor Long (referencing previous assignment setup)
// CITE: TA Eugene Chou for idea help in section
// CITE: TUTOR Brian Mak for helping with valgrind & understanding resetting array each time using a function
// CITE: TA Sloan Liu for the malloc idea

static uint32_t SEED = 13371453; //set default
static uint32_t ELEM = 100;
static uint32_t PR = 100;

void resetting(uint32_t *A, uint32_t SEED, uint32_t ELEM) { // helper function for resetting stats
    uint32_t mask = 0x03FFFFFFF; // bitmask to fit in 30 bits
    srandom(SEED); //random seed
    for (uint32_t i = 0; i < ELEM; i += 1) { //for loop for creating the array
        A[i] = random() & mask;
    }
    return;
}

int main(int argc, char **argv) {

    void (*sort[])() = { &heap_sort, &shell_sort, &insertion_sort,
        &quick_sort }; //function pointer to all sorting functions
    const char *names[] = { "Heap Sort", "Shell Sort", "Insertion Sort",
        "Quick Sort" }; //this is for calling names of the sort

    Set s = empty_set(); //this will be for which command option is called (storing what functions)

    int opt = 0;
    if (argc == 1) { //is there is no arguments print menu
        printf("Select at least one sort to perform.\n");
        printf("SYNOPSIS\n");
        printf("   A collection of comparison-based sorting algorithms.\n");

        printf("\nUSAGE\n");
        printf("   ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]");

        printf("\nOPTIONS\n");
        printf("   -h		   display program help and usage.\n");
        printf("   -a		   enable all sorts.\n");
        printf("   -e		   enable Heap Sort.\n");
        printf("   -i		   enable Insertion Sort.\n");
        printf("   -s		   enable Shell Sort.\n");
        printf("   -q		   enable Quick Sort.\n");
        printf("   -n length	   specify number of array elements (default: 100).\n");
        printf("   -p elements     specify number of elements to print (default: 100).\n");
        printf("   -r seed	   specify random seed (default: 13371453)\n");
    }

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) { //while loop for command lines
        switch (opt) {
        case 'h': // -h (help) prints the menu
            printf("SYNOPSIS\n");
            printf("   A collection of comparison-based sorting algorithms.\n");

            printf("\nUSAGE\n");
            printf("   ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]");

            printf("\nOPTIONS\n");
            printf("   -h              display program help and usage.\n");
            printf("   -a              enable all sorts.\n");
            printf("   -e              enable Heap Sort.\n");
            printf("   -i              enable Insertion Sort.\n");
            printf("   -s              enable Shell Sort.\n");
            printf("   -q              enable Quick Sort.\n");
            printf("   -n length       specify number of array elements (default: 100).\n");
            printf("   -p elements     specify number of elements to print (default: 100).\n");
            printf("   -r seed         specify random seed (default: 13371453)\n");
            break;
        case 'a': // -a (all) prints all
            s = insert_set(HEAP, s);
            s = insert_set(SHELL, s);
            s = insert_set(INSERTION, s);
            s = insert_set(QUICK, s);
            break;
        case 'e': s = insert_set(HEAP, s); break; // -e (heap) sorts array in heap sort
        case 'i':
            s = insert_set(INSERTION, s);
            break; // -e (insertion) sorts array in insertion sort
        case 's': s = insert_set(SHELL, s); break; // -s (shell) sorts array in shell sort
        case 'q': s = insert_set(QUICK, s); break; // -q (quick) sorts array in quick sort
        case 'n':
            ELEM = strtoul(optarg, NULL, 10); // length must need an input
            // this is the length of array
            break;
        case 'p':
            PR = strtoul(optarg, NULL, 10); // must need input
            // this is how many to print
            break;
        case 'r':
            SEED = strtoul(optarg, NULL, 10); // must need input
            // set seed
            break;
        default: //else print the menu
            printf("SYNOPSIS\n");
            printf("   A collection of comparison-based sorting algorithms.\n");

            printf("\nUSAGE\n");
            printf("   ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]");

            printf("\nOPTIONS\n");
            printf("   -h              display program help and usage.\n");
            printf("   -a              enable all sorts.\n");
            printf("   -e              enable Heap Sort.\n");
            printf("   -i              enable Insertion Sort.\n");
            printf("   -s              enable Shell Sort.\n");
            printf("   -q              enable Quick Sort.\n");
            printf("   -n length       specify number of array elements (default: 100).\n");
            printf("   -p elements     specify number of elements to print (default: 100).\n");
            printf("   -r seed         specify random seed (default: 13371453)\n");
            exit(1); //don't continue
        }
    }

    Stats stats; //stats for how many moves and compares
    stats.moves = 0;
    stats.compares = 0;

    //uint32_t mask = 0x03FFFFFFF; // bitmask to fit in 30 bits

    uint32_t *A
        = (uint32_t *) malloc(sizeof(uint32_t) * ELEM); //create an array with random elements

    for (Sorts x = HEAP; x <= QUICK;
         x += 1) { //this is where the elements are called w/ the member_set
        reset(&stats); // reset stats
        resetting(A, SEED, ELEM); // resetting array
        if (member_set(x,
                s)) { //if it is in the member set then call the function that is suppose to be called
            reset(&stats); // reset stats
            sort[x](&stats, A,
                ELEM); //calling the function pointer to the correct sort function
            printf("%s,", names[x]);
            printf(" %" PRIu32 " elements ", ELEM);
            printf("%" PRIu64 " moves", stats.moves);
            printf(" %" PRIu64 " compares\n", stats.compares);
            if (PR
                > ELEM) { //if print size is greater than element size then print how many elements
                for (uint32_t i = 0; i < ELEM; i += 1) {
                    if (i % 5 == 0 && i != 0) { //creating a column of 5
                        printf("\n");
                    }
                    printf("%13" PRIu32, A[i]);
                }
            }
            if (ELEM
                >= PR) { //if elements are equal or greater than print then print how many elements
                for (uint32_t i = 0; i < PR; i += 1) {
                    if (i % 5 == 0 && i != 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, A[i]);
                }
            }
        }
    }
    free(A); //free the array
    return 0;
}

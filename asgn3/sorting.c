#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "haeisqn:p:r:"

typedef enum { INSERTION, SHELL, HEAP, QUICK } Sorts;

//CITE: Professor Long (referencing previous assignment setup)
//CITE: Eugene Chou for idea help in section
// CITE: Brian Mak for helping with valgrind

int main(int argc, char **argv) {

    uint32_t SEED = 13371453;
    uint32_t ELEM = 100;
    uint32_t PR = 100;

    void (*sort[])() = { &insertion_sort, &shell_sort };
    const char *names[] = { "Insertion Sort", "Shell Sort", "Heap Sort", "Quick Sort" };

    Set s = empty_set();

    int opt = 0;
    if (argc == 1) {
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

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
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
        case 'a':
            //s = insert_set(INSERTION, s);
            break;
        case 'e': s = insert_set(HEAP, s); break;
        case 'i': s = insert_set(INSERTION, s); break;
        case 's': s = insert_set(SHELL, s); break;
        case 'q': s = insert_set(QUICK, s); break;
        case 'n':
            ELEM = strtoul(optarg, NULL, 10);
            // this is the length of array
            break;
        case 'p':
            PR = strtoul(optarg, NULL, 10);
            // this is how many to print
            break;
        case 'r':
            SEED = strtoul(optarg, NULL, 10);
            // set seed
            break;
        default:
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
            exit(1);
        }
    }

    Stats stats;
    stats.moves = 0;
    stats.compares = 0;

    uint32_t mask = 0x03FFFFFFF;

    srandom(SEED);
    uint32_t *A = (uint32_t *) malloc(sizeof(uint32_t) * ELEM);
    for (uint32_t i = 0; i < ELEM; i += 1) {
        A[i] = random() & mask;
        // implement a bitmask to fit in 30 bits
    }

    for (Sorts x = INSERTION; x <= QUICK; x += 1) {
        if (member_set(x, s)) {
            reset(&stats);
            sort[x](&stats, A, ELEM);
            printf("%s", names[x]);
            printf(" %" PRIu32 " elements ", ELEM);
            printf("%" PRIu64 " moves", stats.moves);
            printf(" %" PRIu64 " compares\n", stats.compares);
            if (PR > ELEM) {
                for (uint32_t i = 0; i < ELEM; i += 1) {
                    if (i % 5 == 0 && i != 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, A[i]);
                }
            }
            if (ELEM >= PR) {
                for (uint32_t i = 0; i < PR; i += 1) {
                    if (i % 5 == 0 && i != 0) {
                        printf("\n");
                    }
                    printf("%13" PRIu32, A[i]);
                }
            }
            printf("\n");
        }
    }
    free(A);
    return 0;
}

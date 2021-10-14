#include "set.h"
#include "stats.h"
#include "insert.h"
#include "shell.h"
#include "heap.h"
#include "quick.h"

#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#define OPTIONS "[-haeinsqn:p:r:] [-n lenth] [-p elements] [-r seed]"

//CITE: Professor Long (referencing previous assignment setup)
//CITE: Eugene Chou for idea help in section
static uint32_t SEED = 13371453;
static uint32_t LENGTH = 100;
static uint32_t PRINT = 100;

int main(int argc, char **argv) {

	Stats stats;
        stats.moves = 0;
        stats.compares = 0;

	uint32_t mask = 0x03fffffff;

	srandom(SEED);
        uint32_t *A = (uint32_t *)calloc(LENGTH, sizeof(uint32_t));
        for(uint32_t i = 0; i <= LENGTH; i += 1){
                A[i]  = random() & mask;
                // implement a bitmask to fit in 30 bits
        }

	typedef enum {INSERTION, HEAP, SHELL, QUICK} Sorts;
        void (*sort[])() = {&insertion_sort};
	const char *names[] = {"Insertion Sort", "Heap Sort", "Shell Sort", "Quick Sort"};

	Set s = empty_set();

	int opt = 0;
	if(argc == 1){
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
	for (int i = 0; i < argc; i += 1) {
	}
	while ((opt = getopt(argc, argv, OPTIONS)) != -1){
		switch(opt){
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
			case 'e':
			//	s = insert_set(s, HEAP);
				break;
			case 'i':
				s = insert_set(INSERTION, s);
				break;
			case 's':
			//	s = insert_set(s, SHELL);
				break;
			case 'q':
			//	s = insert_set(s, QUICK);
				break;
			case 'n':
				
				// this is the length of array
				break;
			case 'p':
				// this is how many to print
				break;
			case 'r':
				// set seed
				break;
			default:
				printf("./sorting: option requires an argument");
			}
	}

	for (Sorts x = INSERTION; x <= QUICK; x += 1){
		if(member_set(x , s)){
				sort[x](&stats, A, LENGTH);
				printf("%s", names[x]);
				printf(" %d elements ",  LENGTH);
        			printf("%" PRIu64 " moves", stats.moves);
				printf(" %" PRIu64 " compares\n", stats.compares);
				for (uint32_t i = 0; i < PRINT; i += 1){
					if(i % 5 == 0 && i != 0){
                                                printf("\n");
					}
					printf("%13" PRIu32, A[i]);
				}
				printf("\n");
				reset(&stats);
			}
		}
	free(A);
	return 0;
}

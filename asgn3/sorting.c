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

#define OPTIONS "[-haeinsqn:p:r] [-n lenth] [-p elements] [-r seed]"
#define SEED 13371453
#define LENGTH 100
#define PRINT 100


typedef enum {INSERTION, HEAP, SHELL, QUICK, NUM_SORTS} Sorts;
const char *names[] = {"Insertion sort", "Heap sort", "Shell sort", "Quick sort"};

//CITE: Professor Long (referencing previous assignment setup)
//CITE: Eugene Chou for idea help in section

int main(int argc, char **argv) {
	/*Stats stats;
	stats.moves = 0;
	stats.compares = 0;

	Set s = empty_set();
	int opt = 0;

	srandom(SEED);
	uint32_t *A = (uint32_t *)calloc(LENGTH, sizeof(uint32_t));
        for(uint32_t i = 0; i < PRINT; i += 1){
                A[i] = random();
        }*/

	//bool ci = false;
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
	//CITE: Professor Long
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
				printf("prints all");
				break;
			case 'e':
				printf("print heap sort");
				break;
			case 'i':
				s = insert_set(INSERTION, s);
			//	ci = true;
				break;
			case 's':
				printf("shell sort");
				break;
			case 'q':
				printf("quick sort");
				break;
			case 'n':
				printf("number of arrays");
				// get user input for size of array
				break;
			case 'p':
				printf("printing arrays");
				// get user input for elements number, for element array
				break;
			case 'r':
				printf("set seed");
				// get the uyser input for seed
				break;
			}
	}
        Stats stats;
        stats.moves = 0;
        stats.compares = 0;

        //Set s = empty_set();

        srandom(SEED);
        uint32_t *A = (uint32_t *)calloc(LENGTH, sizeof(uint32_t));
        for(uint32_t i = 0; i <= PRINT; i += 1){
                A[i] = random();
        }


	//if(ci)
	for (Sorts x = INSERTION; x < PRINT; x += 1){
		if (member_set(x, s)){
			//	printf("elements = %d\n",  LENGTH);
                        //	printf("moves = %" PRIu64 "\n", stats.moves);
                        //	printf("compares = %" PRIu64 "\n", stats.compares);
			
			insertion_sort(&stats, A, LENGTH);
		
		printf("%" PRIu32, A[x]);
		if(x+1 != 100){
			printf(", \n");
		}
		}
	}

	/*printf("elements = %d\n",  LENGTH);
        printf("moves = %" PRIu64 "\n", stats.moves);
        printf("compares = %" PRIu64 "\n", stats.compares);
	*/
	return 0;
}

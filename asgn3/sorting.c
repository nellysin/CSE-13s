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


typedef enum {INSERTION, HEAP, SHELL, QUICK} Sorts;
const char *names[] = {"Insertion Sort", "Heap Sort", "Shell Sort", "Quick Sort"};

//CITE: Professor Long (referencing previous assignment setup)
//CITE: Eugene Chou for idea help in section

int main(int argc, char **argv) {
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
				s = insert_set(HEAP, s);
				break;
			case 'i':
				s = insert_set(INSERTION, s);
				break;
			case 's':
				s = insert_set(SHELL, s);
				break;
			case 'q':
				s = insert_set(QUICK, s);
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
			}
	}

	srandom(SEED);
	uint32_t *A = (uint32_t *)calloc(LENGTH, sizeof(uint32_t));
	for(uint32_t i = 0; i <= LENGTH; i += 1){
		A[i] = random();
	}

	Stats stats;
	stats.moves = 0;
	stats.compares = 0;

	for (Sorts x = INSERTION; x < QUICK; x += 1){
		if (member_set(x, s)){
			if(x == 0){
				insertion_sort(&stats, A, 100);
				for (uint32_t i = 0; i < 100; i += 1){
					printf("%" PRIu32, A[i]);
					if(i+1 != 100){
						printf(",  \n");
					}
				}
			}
		}
		//same with heap, quick, shell
	}
	free(A);
	return 0;
}

#include "insert.h"
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SEED 13371453
#define LENGTH 100
#define ELEM 100
#define OPTIONS [-haeinsqn:p:r] [-n lenth] [-p elements] [-r seed]

//CITE: Professor Long (referencing previous assignment setup)

int main(int arc, char **argv) {
	int opt = 0;
	bool ce = false;
	bool ci = false;
	bool cs = false;
	bool cq = false;
	bool cn = false;
	bool cp = false;
	bool cr = false;
	if(argc == 1){
		printf("Select at least one sort to perform.\n");
		printf("SYNOPSIS\n");
		prtinf("   A collection of comparison-based sorting algorithms.\n");
		
		printf("\nUSAGE\n");
		printf("   ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]");

		printf("\nOPTIONS\n");
		printf("   -h		   display program help and usage.");
		printf("   -a		   enable all sorts.");
		printf("   -e		   enable Heap Sort.");
		printf("   -i		   enable Insertion Sort.");
		printf("   -s		   enable Shell Sort.");
		printf("   -q		   enable Quick Sort.");
		printf("   -n length	   specify number of array elements (default: 100).");
		printf("   -p elements     specify number of elements to print (default: 100).");
		printf("   -r seed	   specify random seed (default: 13371453)");
	}
	//CITE: Professor Long
	for (int i = 0; i < argc; i += 1) {
	}
	while ((opt = getopt(argc, argv, OPTIONS)) != -1){
		switch(opt){
			case 'h':
                		printf("SYNOPSIS\n");
                		prtinf("   A collection of comparison-based sorting algorithms.\n");

                		printf("\nUSAGE\n");
                		printf("   ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]");

                		printf("\nOPTIONS\n");
                		printf("   -h              display program help and usage.");
                		printf("   -a              enable all sorts.");
                		printf("   -e              enable Heap Sort.");
                		printf("   -i              enable Insertion Sort.");
                		printf("   -s              enable Shell Sort.");
                		printf("   -q              enable Quick Sort.");
                		printf("   -n length       specify number of array elements (default: 100).");
                		printf("   -p elements     specify number of elements to print (default: 100).");
                		printf("   -r seed         specify random seed (default: 13371453)");
				break;
			case 'a':
				ce = ci = cs = cq = true;
				break;
			case 'e':
				ce = true;
				break;
			case 'i':
				ci = true;
				break;
			case 's':
				cs = true;
				break;
			case 'q':
				cq = true;
				break;
			case 'n':
				cn = true;
				// get user input for size of array
				break;
			case 'p':
				// get user input for elements number, for element array
				cp = true;
				break;
			case 'r':
				cr = true;
				// get the uyser input for seed
				break;
			}
	}
	//create if statement for each input:
	//if a = true
	//	if n or p or r is true 
	//	set seed, size, and element number to a variable 
	//	call function with the user's input of size, element, and element number
	//if e = true
	//	if n or p or r is true
	//	set them to a variable 
	//	call heap sort with the variables
	//if i = true
	//	if n or p or r is true
	//	set them to a variable
	//	call insertion sort function and set variables
	//CONTINUE WITH SHELL AND QUICK SORT FUNCTIONS.
	//each statement will print out their stats (stats.c)
}

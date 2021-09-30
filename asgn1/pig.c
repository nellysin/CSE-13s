#include <stdio.h>
#include <stdlib.h>
#include "names.h"
#include <limits.h>		// CITE: limits.h & inttypes.h by TUTOR: BEN GRANT
#include <inttypes.h>

#define SEED 2021

typedef enum {SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
const Position pig[7] = {
	SIDE,
	SIDE,
	RAZORBACK,
	TROTTER,
	SNOUTER,
	JOWLER,
	JOWLER
};

int main (void) {

	int users = 0;		//get user input
	// printf first
	printf("How many players? ");
	scanf("%d", &users);

	if (users < 2 || users > 10)
	{						  // check invalid input
		fprintf(stderr, "Invalid number of players. Using 2 instead.\n"); //standard error
	}


	// printf
	printf("Random seed: ");
	int64_t seed = 0;
	scanf("%" SCNd64, &seed);	//CITE: int64_t with seed TUTOR: BEN GRANT
	if (seed > UINT_MAX || seed < 0)
	{
		seed = SEED;
       		fprintf(stderr , "Invalid  random  seed. Using  2021  instead .\n"); // standard error
	}

	int points[10] = {0};                         //set a points array (keep track of scores) with 10 spaces

	for (int i = 0; i < users; i += 1)		// for each player 
	{
		printf("%s rolls the pig... ", names[i]);		
		srandom(SEED);
		int roll;
       		 do {
                	roll = random() % 7;			//rolling in while loop 
			if (pig[roll] == 0 ||pig[roll] == 1)
			{
				printf(" pig lands on side");
				int start = 0;
				if (i == users)
				{
					i = start;
				}
				else{
					i += 1;
					printf("\n%s rolls the pig... ", names[i]);
				}
			}
			if (pig[roll] == 2)				//categorize the type of side the pig is on
			{
				printf(" pig lands on back");	// print the position (cannot print enumeration)
				points[i] += 10; // add 10 to points
			}
			if (pig[roll] == 3)
			{
				printf(" pig lands upright");
				points[i] += 10;
			}
			if (pig[roll] == 4)
			{
				printf(" pig lands on snout");
				points[i] += 15; // add 15 to points
			}

			if (pig[roll] == 5 || pig[roll] == 6)
			{
				printf(" pig lands on ear");
				points[i] += 5;// add 5 to points
			}

        	} while (points[i] < 100);
		printf("\n");
		printf("%s wins with %d\n ",names[i], points[i]);  // announce winner
                break;

		// print the position (cannot print enumeration)
		 //and if it's the last player go back to the first player (same thing with points)
		 // continue in a for loop
	}
}

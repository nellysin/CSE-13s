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

	for (int i = 0; i == users; i += 1)		// for each player 
	{
		int points[10]; 			//set a pointer to the array
							// how to fill an array (?)
		printf("%s",names[i]);			
		srandom(SEED);
		int roll;
		if (points[i] >= 100)			// if check points if its >= 100
		{
			printf("%s wins with %d",names[i], points[i]);	// announce winner
			break;
			return 0;
		}
       		 do {							// CITE: do {} while loop from tutor
                	roll = random() % users;			//rolling in while loop 
			if (pig[roll] == 2)				//categorize the type of side the pig is on
			{
				printf("razorback");	// print the position (cannot print enumeration)
				points[i] += 10; // add 10 to points	//add points
			}
			if (pig[roll] == 3)
			{
				printf("trotter");
				points[i] += 10;
			}
			if (pig[roll] == 4)
			{
				printf("snouter")
				points[i] += 15; // add 15 to points
			}

			if (pig[roll] == 5 || pig[roll] == 6)
			{
				print("jowler")
				points[i] += 5;// add 5 to points
			}

        	} while (roll != 0 || roll != 1);
		// print the position (cannot print enumeration)

		if (i == users)
		{
			int i = 0;
		}
		 //and if it's the last player go back to the first player (same thing with points)
		 // continue in a for loop
	}
}

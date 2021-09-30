#include "names.h"

#include <inttypes.h>
#include <limits.h> // CITE: limits.h & inttypes.h by TUTOR: BEN GRANT
#include <stdio.h>
#include <stdlib.h>

#define SEED 2021

typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };

int main(void) {

    int users = 0; //get user input
    printf("How many players? ");
    scanf("%d", &users);

    if (users < 2 || users > 10) { // check invalid input
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n"); //standard error
    }

    printf("Random seed: ");
    int64_t seed = 0;
    scanf("%" SCNd64, &seed); //CITE: int64_t with seed TUTOR: BEN GRANT
    if (seed > UINT_MAX || seed < 0) {
        seed = SEED;
        fprintf(stderr, "Invalid  random  seed. Using  2021  instead .\n"); // standard error
    }
    int points[10] = { 0 }; //set a points array (keep track of scores) with 10 spaces
    int i = 0;
    int USER = users - 1;
    while(i != users){
	srandom(SEED);
        int roll;
        do {
           roll = random() % 7; //rolling in while loop
           if (pig[roll] == 0 || pig[roll] == 1) {
                printf(" pig lands on side");
		if (i == USER) // if it's the last player
                {
		    printf("\n%s rolls the pig...", names[i]);
                    i = 0; // restart OR continue to the next player
                } else{
			printf("\n%s rolls the pig...", names[i]);
			i += 1;	
		}
            } else if (pig[roll] == 2) //categorize the type of side the pig is on
            {
                printf(" pig lands on back"); // print the position (cannot print enumeration)
                points[i] += 10; // add 10 to points
            } else if (pig[roll] == 3) {
                printf(" pig lands upright");
                points[i] += 10;
            } else if (pig[roll] == 4) {
                printf(" pig lands on snout");
                points[i] += 15; // add 15 to points
            } else if (pig[roll] == 5 || pig[roll] == 6) {
                printf(" pig lands on ear");
                points[i] += 5; // add 5 to points
            }

        } while (points[i] < 100);
	if (points[i] >= 100)
	{
        	printf("\n");
        	printf("%s wins with %d\n", names[i], points[i]); // announce winner
        	break;
	}

    }
}

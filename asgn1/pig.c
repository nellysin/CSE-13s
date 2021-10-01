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
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        users = 2; //standard error
    }

    printf("Random seed: ");
    int64_t seed = 0;
    scanf("%" SCNd64, &seed); //CITE: int64_t with seed TUTOR: BEN GRANT
    if (seed > UINT_MAX || seed < 0) {
        seed = SEED;
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n"); // standard error
    }
    int points[10] = { 0 }; //set a points array (keep track of scores) with 10 spaces

    users = users - 1;
    int roll;
    int i = 0;
    printf("%s rolls the pig...", names[i]);
    srandom(seed);
    do {
        roll = random() % 7;
        switch (pig[roll]) {
        case SIDE: printf(" pig lands on side\n"); break;
        case RAZORBACK:
            printf(" pig lands on back"); // print the position (cannot print enumeration)
            points[i] += 10; // add 10 to points
            break;
        case TROTTER:
            printf(" pig lands upright");
            points[i] += 10;
            break;
        case SNOUTER:
            printf(" pig lands on snout");
            points[i] += 15; // add 15 to points
            break;
        case JOWLER:
            printf(" pig lands on ear");
            points[i] += 5; // add 5 to points
            break;
        }

        if (points[i] >= 100) { // check if a player points > 100
            printf("\n");
            printf("%s wins with %d points!\n", names[i], points[i]);
            break;
        }
        if (roll == 1
            || roll
                   == 0) { // if roll = SIDE then skip to the next player or restart from the first player
            if (i == users) {
                i = 0;
                printf("%s rolls the pig...", names[i]);
            } else {
                i += 1;
                printf("%s rolls the pig...", names[i]);
            }
        }
    } while (points[i] < 100 || roll != 1
             || roll != 0); //continue rolling the dice only if points < 100, roll != side
    return 0;
}

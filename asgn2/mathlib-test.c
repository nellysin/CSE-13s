#include <stdio.h>
#include <unistd.h>
#include "mathlib.h"

#define OPTIONS "pi:"

int main(int argc, char **argv){
	int opt = 0;
	if (argv[0]){
		printf("SYNOPSIS\n");
		printf("   A test harness for the small numerical library.\n");

		printf("\nUSAGE\n");
		printf("   ./mathlib-test [-aebmrvnsh]\n");

		printf("\nOPTIONS\n");
		printf("   -a: Runs all tests.\n");
		printf("   -e: Runs e approximation test.\n");
		printf("   -b: Runs Bailey-Borwein-Plouffe π approximation test.\n");
		printf("   -m: Runs Madhava π approximation test.\n");
		printf("   -r: Runs Euler sequence π approximation test.\n");
		printf("   -v: Runs Viète π approximation test.\n");
		printf("   -n: Runs Newton-Raphson square root approximation tests.\n");
		printf("   -s: Enable printing of statistics to see computed terms and factors for each tested function.\n");
		printf("   -h: Display a help message detailing program usage.\n");
	}
	while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch (opt) {
			case 'a':
				printf("-a: Runs all tests.\n");
				break;
			case 'e':
				printf("-e: Runs e approximation test.\n");
				break;
			case 'b':
				printf("-b: Runs Bailey-Borwein-Plouffe π approximation test.\n");
				break;
			case 'm':
				printf("Runs Madhava π approximation test.\n");
				break;
			case 'r':
				printf("Runs Euler sequence π approximation test.\n");
				break;
			case 'v':
				printf("Runs Viète π approximation test.\n");
				break;
			case 'n':
				printf("Runs Newton-Raphson square root approximation tests.\n");
				break;
			case 's':
                                printf("Enable printing of statistics to see computed terms and factors for each tested function.\n");
				break;
			case 'h':
				printf("Display a help message detailing program usage.\n");
				break;
		}
	}
	return 0;
}

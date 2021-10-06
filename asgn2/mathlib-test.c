#include <stdio.h>
#include <unistd.h>
#include "mathlib.h"
#include <math.h>

#define OPTIONS "[-aebmrvnsh]"

int main(int argc, char **argv){ // CITED: Professor Long
	//getopt() loop should just parse CLI options
	int opt = 0;
	if (argc == 1){
		printf("SYNOPSIS\n");
		printf("   A test harness for the small numerical library.\n");

		printf("\nUSAGE\n");
		printf("   ./mathlib-test %s\n",OPTIONS);

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
	for (int i = 0; i < argc; i += 1){ //CITED: Professor Long set code
	}
	while ((opt = getopt(argc, argv, OPTIONS)) != -1) { //CITED: Professor Long (while & switch case)
		switch (opt) {
			case 'a':
				printf("Runs all tests.\n");
				break;
			case 'e':
				printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(e() - M_E));
				break;
			case 'b':
				printf("Runs Bailey-Borwein-Plouffe π approximation test.\n");
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
			default:
				break;
		}
	}
	return 0;
}

#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "[-aebmrvnsh]"

int main(int argc, char **argv) { // CITED: Professor Long
    //getopt() loop should just parse CLI options
    int opt = 0;
    bool ce = false;
    bool cb = false;
    bool cm = false;
    bool cr = false;
    bool cv = false;
    bool cn = false;
    bool cs = false;
    if (argc == 1) {
        printf("SYNOPSIS\n");
        printf("   A test harness for the small numerical library.\n");

        printf("\nUSAGE\n");
        printf("   ./mathlib-test %s\n", OPTIONS);

        printf("\nOPTIONS\n");
        printf("   -a: Runs all tests.\n");
        printf("   -e: Runs e test.\n");
        printf("   -b: Runs BBP pi test.\n");
        printf("   -m: Runs Madhava pi test.\n");
        printf("   -r: Runs Euler pi test.\n");
        printf("   -v: Runs Viete pi test.\n");
        printf("   -n: Runs Newton square root tests.\n");
        printf("   -s: Print verbose statistics.\n");
        printf("   -h: Display program synopsis and usage.\n");
    }
    for (int i = 0; i < argc; i += 1) { //CITED: Professor Long set code
    }
    while (
        (opt = getopt(argc, argv, OPTIONS)) != -1) { //CITED: Professor Long (while & switch case)
        switch (opt) {
        case 'a': //if selected -a
            ce = true; // CITE: Eugene showed example in section (booleans)
            cr = true;
            cb = true;
            cm = true;
            cv = true;
            cn = true;
            break;
        case 'e': ce = true; break; //if selected -e
        case 'b': cb = true; break; //if selected -b
        case 'm': cm = true; break; //if selected -m
        case 'r': cr = true; break; //if selected -r
        case 'v': cv = true; break; //if selected -v
        case 'n': cn = true; break; //if selected -n
        case 's': cs = true; break; //if selected -s
        case 'h': //if selected -h
            printf("SYNOPSIS\n");
            printf("   A test harness for the small numerical library.\n");

            printf("\nUSAGE\n");
            printf("   ./mathlib-test %s\n", OPTIONS);

            printf("\nOPTIONS\n");
            printf("   -a: Runs all tests.\n");
            printf("   -e: Runs e test.\n");
            printf("   -b: Runs BBP pi test.\n");
            printf("   -m: Runs Madhava pi test.\n");
            printf("   -r: Runs Euler pi test.\n");
            printf("   -v: Runs Viete pi test.\n");
            printf("   -n: Runs Newton square root tests.\n");
            printf("   -s: Print verbose statistics.\n");
            printf("   -h: Display program synopsis and usage.\n");
            break;
        default: break;
        }
    }
    if (ce == true) { //switch cases will go to one of these if statements
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(e() - M_E));
        if (cs == true) {
            printf("e() terms = %d\n", e_terms());
        }
    }
    if (cr == true) {
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
            absolute(pi_euler() - M_PI));
        if (cs == true) {
            printf("pi_euler terms = %d\n", pi_euler_terms());
        }
    }
    if (cb == true) {
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
            absolute(pi_bbp() - M_PI));
        if (cs == true) {
            printf("pi_bbp terms = %d\n", pi_bbp_terms());
        }
    }
    if (cm == true) {
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
            absolute(pi_madhava() - M_PI));
        if (cs == true) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }
    if (cv == true) {
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
            absolute(pi_viete() - M_PI));
        if (cs == true) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }
    if (cn == true) {
        for (double i = 0.0; i <= 10; i += 0.1) {
            printf("sqrt_newton(%.6f) = %16.15lf, sqrt(%.6f) = %16.15lf, diff = %16.15lf\n", i,
                sqrt_newton(i), i, sqrt(i), absolute(sqrt_newton(i) - sqrt(i)));
            if (cs == true) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }
    if (cs == true) {
        if (ce == false && cb == false && cr == false && cn == false && cm == false
            && cv == false) {
            printf("SYNOPSIS\n");
            printf("   A test harness for the small numerical library.\n");

            printf("\nUSAGE\n");
            printf("   ./mathlib-test %s\n", OPTIONS);

            printf("\nOPTIONS\n");
            printf("   -a: Runs all tests.\n");
            printf("   -e: Runs e test.\n");
            printf("   -b: Runs BBP pi test.\n");
            printf("   -m: Runs Madhava pi test.\n");
            printf("   -r: Runs Euler pi test.\n");
            printf("   -v: Runs Viete pi test.\n");
            printf("   -n: Runs Newton square root tests.\n");
            printf("   -s: Print verbose statistics.\n");
            printf("   -h: Display program synopsis and usage.\n");
        }
    }
    return 0;
}

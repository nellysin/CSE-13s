# Assignment 2 - A Little Slice of Pi

In this assignment, mathlib-test is where it lists options of mathematical equations and series to approximate
the value of e, square root, and pi. 
The program accepts the following:
	-a: Run all the tests of each function.
	-e: Runs the e approximation test by Taylor series.
	-b: Runs the pi approximation test using Bailey=Borwein-Plouffe (BBP).
	-m: Runs the pi approximation test using the Madhava series.
	-r: Runs the pi approximation test using the Euler sequence.
	-v: Runs the pi approximation test using Viete.
	-n: Runs the square root approximation test using the Newton-Raphson square root.
	-s: Showcase how many terms the selected function ran.
	-h: Display the list of options to the user if help needed.

The purpose of the program is to build our own version of math.h by using the different equation to approximate
e, square root, and pi. It is also to test our accuracy of the program's approximation to the math.h. 

## Building

```
C = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

$(CC) -o mathlib-test mathlib-test.o e.o newton.o bbp.o euler.o madhava.o viete.o $(LFLAGS)
$(CC) -o euler euler.o newton.o $(LFLAGS)
$(CC) -o madhava madhava.o newton.o $(LFLAGS)
$(CC) -o viete viete.o newton.o $(LFLAGS)

$ clang -Wall -Wextra -Werror -Wpedantic -o mathlib-test mathlib-test.c
$ clang -Wall -Wextra -Werror -Wpedantic -o e e.c
$ clang -Wall -Wextra -Werror -Wpedantic -o newton newton.c
$ clang -Wall -Wextra -Werror -Wpedantic -o bbp bbp.c
$ clang -Wall -Wextra -Werror -Wpedantic -o euler euler.c
$ clang -Wall -Wextra -Werror -Wpedantic -o madhava madhava.c
$ clang -Wall -Wextra -Werror -Wpedantic -o viete viete.c
```

## Running

This program is designed to run in Ubuntu, Linux in C program with:

```
$ ./mathlib-test -(OPTION
```

## Bugs:

Currently, no known bugs.

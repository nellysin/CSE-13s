C = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: mathlib-test

mathlib-test: mathlib-test.o
	$(CC) -o pig pig.o

mathlib-test.o: mathlib-test.c mathlib.h
	$(CC) $(CFLAGS) -c mathlib-test.c

clean:
	rm -f mathlib-test mathlib-test.o

format:
	clang-format -i -style=file *.{ch}

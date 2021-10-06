C = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: e.o bbp.o newton.o euler.o mathlib-test.o

mathlib-test: mathlib-test.o e.o newton.o bbp.o euler.o
	$(CC) -o mathlib-test mathlib-test.o e.o newton.o bbp.o euler.o $(LFLAGS)

euler: euler.o newton.o
	$(CC) -o euler euler.o newton.o $(LFLAGS)

mathlib-test.o: mathlib-test.c
	$(CC) $(CFLAGS) -c mathlib-test.c

e.o: e.c
	$(CC) $(CFLAGS) -c e.c

newton.o: newton.c
	$(CC) $(CFLAGS) -c newton.c

bbp.o: bbp.o
	$(CC) $(CFLAGS) -c bbp.c

euler.o: euler.c
	$(CC) $(CFLAGS) -c euler.c

clean:
	rm -f mathlib-test *.o

format:
	clang-format -i -style=file *.{ch}

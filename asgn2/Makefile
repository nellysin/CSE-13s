C = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: mathlib-test

mathlib-test: mathlib-test.o e.o newton.o bbp.o euler.o madhava.o viete.o
	$(CC) -o mathlib-test mathlib-test.o e.o newton.o bbp.o euler.o madhava.o viete.o $(LFLAGS)

euler: euler.o newton.o
	$(CC) -o euler euler.o newton.o $(LFLAGS)

madhava: madhava.o newton.o
	$(CC) -o madhava madhava.o newton.o $(LFLAGS)

viete: viete.o newton.o
	$(CC) -o viete viete.o newton.o $(LFLAGS)

mathlib-test.o: mathlib-test.c mathlib.h
	$(CC) $(CFLAGS) -c mathlib-test.c

e.o: e.c mathlib.h
	$(CC) $(CFLAGS) -c e.c

newton.o: newton.c mathlib.h
	$(CC) $(CFLAGS) -c newton.c

bbp.o: bbp.o mathlib.h
	$(CC) $(CFLAGS) -c bbp.c

euler.o: euler.c mathlib.h
	$(CC) $(CFLAGS) -c euler.c

madhava.o: madhava.c mathlib.h
	$(CC) $(CFLAGS) -c madhava.c

viete.o: viete.c mathlib.h
	$(CC) $(CFLAGS) -c viete.c

clean:
	rm -f mathlib-test mathlib-test.o
	rm -f e e.o
	rm -f newton newton.o
	rm -f bbp bbp.o
	rm -f madhava madhava.o
	rm -f viete viete.o
	rm -f euler euler.o

format:
	clang-format -i -style=file *.[ch]

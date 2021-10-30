CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: code

code: code.o stack.o
	$(CC) -o code code.o stack.o $(LFLAGS)

io.o: io.c io.h code.h
	$(CC) $(CFLAGS) -c io.c

stack.o: stack.c stack.h defines.h code.h
	$(CC) $(CLFAGS) -c stack.c

code.o: code.c code.h defines.h code.h
	$(CC) $(CFLAGS) -c code.c

clean:
	rm -f *.o

format:
	clang-format -i -style=file *.[ch]

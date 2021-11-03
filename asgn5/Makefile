CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: pq

code: code.o stack.o
	$(CC) -o code code.o stack.o $(LFLAGS)

pq: pq.o node.o
	$(CC) -o pq pq.o node.o $(LFLAGS)

io.o: io.c io.h code.h
	$(CC) $(CFLAGS) -c io.c

stack.o: stack.c stack.h defines.h code.h
	$(CC) $(CLFAGS) -c stack.c

code.o: code.c code.h defines.h code.h
	$(CC) $(CFLAGS) -c code.c

pq.o: pq.c pq.h node.h
	$(CC) $(CFLAGS) -c pq.c

clean:
	rm -f *.o

format:
	clang-format -i -style=file *.[ch]

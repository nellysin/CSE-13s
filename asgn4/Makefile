CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: 

path: path.o graph.o stack.o
	$(CC) -o path path.o graph.o stack.o $(LFLAGS)

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

path.o: path.c path.h graph.h stack.h
	$(CC) $(CFLAGS) -c path.c

clean:
	rm -f graph graph.o
	rm -f stack stack.o
	rm -f path path.o
	
format:
	clang-format -i -style=file *.[ch]

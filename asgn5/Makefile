CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: encode decode 

encode: encode.o node.o pq.o stack.o io.o huffman.o
	$(CC) -o encode encode.c 

decode: decode.o node.o pq.o stack.o io.o huffman.o
	$(CC) -o decode decode.c 

huffman.o: huffman.c huffman.h code.h defines.h node.h pq.h
	$(CC) $(CFLAGS) -c huffman.c

encode.o: encode.c defines.h
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.o defines.h
	$(CC) $(CFLAGS) -c decode.c

node.o: node.h
	$(CC) $(CFLAGS) -c node.c

stack.o: stack.h node.c node.h
	$(CC) $(CFLAGS) -c stack.c

pq.o: pq.h node.c node.h
	$(CC) $(CFLAGS) -c pq.c

code.o: code.h node.c node.h
	$(CC) $(CFLAGS) -c code.c

io.o: io.h
	$(CC) $(CFLAGS) -c code.c

clean:
	rm -f *.o

format:
	clang-format -i -style=file *.[ch]

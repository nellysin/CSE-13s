CC = clang
CFLAGS = -g -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: encode decode

encode: encode.o node.o stack.o pq.o io.o huffman.o code.o
	$(CC) -o encode encode.o node.o stack.o pq.o io.o huffman.o code.o

decode: decode.o node.o stack.o pq.o io.o huffman.o code.o
	$(CC) -o decode decode.o node.o stack.o pq.o io.o huffman.o code.o

huffman.o: huffman.c huffman.c huffman.h code.h defines.h node.h pq.h io.h stack.h
	$(CC) $(CFLAGS) -c huffman.c

encode.o: encode.c defines.h huffman.h code.h node.h pq.h io.h stack.h header.h
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c defines.h huffman.h code.h node.h pq.h io.h stack.h header.h
	$(CC) $(CFLAGS) -c decode.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

stack.o: stack.h node.c node.h
	$(CC) $(CFLAGS) -c stack.c

pq.o: pq.c pq.h node.c node.h
	$(CC) $(CFLAGS) -c pq.c

code.o: code.c code.h node.c node.h
	$(CC) $(CFLAGS) -c code.c

io.o: io.c io.h defines.h code.h
	$(CC) $(CFLAGS) -c io.c

clean:
	rm -f *.o

format:
	clang-format -i -style=file *.[ch]

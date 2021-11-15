CC = clang
CFLAGS = -g -Wall -Werror -Wextra -Wpedantic $(shell pkg-config -- cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)

all: keygen encrypt decrypt 

#LINKING
keygen: keygen.o 
	$(CC) -o keygen keygen.o $(LFLAGS)

encrypt: encrypt.o
	$(CC) -o encrypt encrypt.o $(LFLAGS)

decrypt: decrypt.o
	$(CC) -o decrypt decrypt.o $(LFLAGS)

#OBJECT FILES
keygen.o: keygen.c randstate.h numtheory.h rsa.h
	$(CC) $(CFLAGS) -c keygen.c

encrypt.o: encrypt.c randstate.h numtheory.h rsa.h
	$(CC) $(CFLAGS) -c encrypt.c

decript.o: decrypt.c randstate.h numtheory.h rsa.h
	$(CC) $(CFLAGS) -c decrypt.c

randstate.o: randstate.c randstate.h
	$(CC) $(CFLAGS) -c randstate.c

numtheory.o: numtheory.c numtheory.h
	$(CC) $(CFLAGS) -c numtheory.c

rsa.o: rsa.c rsa.h
	$(CC) $(CFLAGS) -c rsa.c

#CLEANING
clean:
	rm -f keygen *.o
	rm -f decrypt *.o
	rm -f encrypt *.o

#FORMATING
format:
	clang-format -i -style=file *.[ch]

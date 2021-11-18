CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic $(shell pkg-config -- cflags gmp)
LFLAGS = -g $(shell pkg-config --libs gmp)

all: keygen encrypt decrypt 

#LINKING
keygen: keygen.o rsa.o randstate.o numtheory.o
	$(CC) -o keygen keygen.o rsa.o randstate.o numtheory.o $(LFLAGS)

encrypt: encrypt.o rsa.o randstate.o numtheory.o
	$(CC) -o encrypt encrypt.o rsa.o randstate.o numtheory.o $(LFLAGS)

decrypt: decrypt.o rsa.o randstate.o numtheory.o
	$(CC) -o decrypt decrypt.o rsa.o randstate.o numtheory.o $(LFLAGS)

#OBJECT FILES
keygen.o: keygen.c
	$(CC) $(CFLAGS) -c keygen.c

encrypt.o: encrypt.c
	$(CC) $(CFLAGS) -c encrypt.c

decript.o: decrypt.c 
	$(CC) $(CFLAGS) -c decrypt.c

randstate.o: randstate.c
	$(CC) $(CFLAGS) -c randstate.c

numtheory.o: numtheory.c
	$(CC) $(CFLAGS) -c numtheory.c

rsa.o: rsa.c rsa.h
	$(CC) $(CFLAGS) -c rsa.c

#CLEANING
clean:
	rm -f *.{pub,priv}
	rm -f keygen *.o
	rm -f decrypt *.o
	rm -f encrypt *.o

#FORMATING
format:
	clang-format -i -style=file *.[ch]

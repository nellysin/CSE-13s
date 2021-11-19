# Assignment 6 - Public Key Cryptography

In this assignment, we are implementing public key cryptography. 
Public-key cryptography is a cryptographic system that uses pairs of keys. One is public keys (can be used to others) and private keys (owned only by the owner).
Anyone can encrypt a message with the right public key, but the owner of the private key will be the only one who can decrypt the message. 
The keys are a shared secret -- similar to how we text message friends --between two parties.
Since it is a requirement that both parties have access to the secret key is a disadvantage to the encryption comparing to the public-key encryption.

## Building

```
CC = clang
CFLAGS = -g -Wall -Werror -Wextra -Wpedantic $(shell pkg-config -- cflags gmp)
LFLAGS =  $(shell pkg-config --libs gmp)

all: keygen encrypt decrypt

### LINKING

keygen: keygen.o rsa.o randstate.o numtheory.o
        $(CC) -o keygen keygen.o rsa.o randstate.o numtheory.o $(LFLAGS)

encrypt: encrypt.o rsa.o randstate.o numtheory.o
        $(CC) -o encrypt encrypt.o rsa.o randstate.o numtheory.o $(LFLAGS)

decrypt: decrypt.o rsa.o randstate.o numtheory.o
        $(CC) -o decrypt decrypt.o rsa.o randstate.o numtheory.o $(LFLAGS)

### OBJECT FILES

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
```

## Running

This Program is designed to run on Ubuntu, Linux in C program with:

```
$./keygen [-hv] [-b bits] -n pbfile -d pvfile
```

```
$./encrypt [-hv] [-i infile] [-o outfile] -n pubkey
```

```
$./decrypt [-hv] [-i infile] [-o outfile] -n privkey
```

## Bugs
Currently, no known current bugs.


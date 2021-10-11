C = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: insert

insert.o: insert.c insert.h
	$(CC) $(CFLAGS) -c insert.c

clean:
	rm -f insert insert.o

format:
	clang-format -i style=file *.[ch]

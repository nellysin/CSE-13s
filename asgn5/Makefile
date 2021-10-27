CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

io.o: io.c io.h code.h
	$(CC) $(CFLAGS) -c io.c

clean:
	rm -f io.o

format:
	clang-format -i -style=file *.[ch]


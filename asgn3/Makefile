C = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

all: sorting

sorting: sorting.o insert.o stats.o
	$(CC) -o sorting sorting.o insert.o stats.o $(LFLAGS)

insert: insert.o stats.o
	$(CC) -o insert insert.o stats.o $(LFLAGS)

sorting.o: sorting.c insert.h set.h stats.h
	$(CC) $(CFLAGS) -c sorting.c

insert.o: insert.c insert.h set.h stats.h
	$(CC) $(CFLAGS) -c insert.c

stats.o: stats.c stats.h 
	$(CC) $(CFLAGS) -c stats.c

clean:
	rm -f sorting sorting.o
	rm -f insert insert.o

format:
	clang-format -i style=file *.[ch]

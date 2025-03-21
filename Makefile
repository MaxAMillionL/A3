CC = gcc217  # Use standard gcc compiler
CFLAGS = -Wall -Wextra -g  # Enable warnings and debugging symbols

all: testsymtablelist testsymtablehash

testsymtablelist: symtablelist.o testsymtable.o
	$(CC) symtablelist.o testsymtable.o -o testsymtablelist

symtablelist.o: symtablelist.c symtable.h
	$(CC) $(CFLAGS) -c symtablelist.c

testsymtable.o: testsymtable.c symtable.h
	$(CC) $(CFLAGS) -c testsymtable.c

testsymtablehash: symtablehash.o testsymtable.o
	$(CC) symtablehash.o testsymtable.o -o testsymtablehash

symtablehash.o: symtablehash.c symtable.h
	$(CC) $(CFLAGS) -c symtablehash.c

clean:
	rm -f *.o testsymtablelist testsymtablehash

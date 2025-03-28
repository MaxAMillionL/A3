all: testsymtablelist testsymtablehash

clobber: clean
	rm -f *~ \#*\#
	
clean:
	rm -f testsymtablelist testsymtablehash *.o

testsymtablelist: symtablelist.o testsymtablelist.o
	gcc217 symtablelist.o testsymtablelist.o -o testsymtablelist

symtablelist.o: symtablelist.c symtable.h
	gcc217 -c symtablelist.c

testsymtablehash: symtablehash.o testsymtablehash.o
	gcc217 symtablehash.o testsymtablehash.o -o testsymtablehash

symtablehash.o: symtablehash.c symtable.h
	gcc217 -c symtablehash.c
	
testsymtablelist.o: testsymtable.c symtable.h
	gcc217 -c testsymtable.c
	mv testsymtable.o testsymtablelist.o

testsymtablehash.o: testsymtable.c symtable.h
	gcc217 -c testsymtable.c
	mv testsymtable.o testsymtablehash.o
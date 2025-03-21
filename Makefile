all: testsymtablelist testsymtablehash

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

testsymtablehash.o: testsymtable.c symtable.h
	gcc217 -c testsymtable.c
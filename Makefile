all: testsymtablelist  testsymtablehash
	gcc217 symtablelist.o testsymtable.o -o testsymtablelist 
	gcc217 symtablehash.o testsymtable.o -o testsymtablehash

symtablelist.o: symtablelist.c symtable.h
	gcc217 -c symtablelist.c

testsymtable.o: testsymtable.c symtable.h
	gcc217 -c testsymtable.c

symtablehash.o: symtablehash.c symtable.h
	gcc217 -c symtablehash.c
testsymtable: symtablelist.o testsymtable.o
	gcc217 symtablelist.o testsymtable.o -o testsymtable

symtablelist.o: symtablelist.c symtable.h
	gcc217 -c symtablelist

testsymtable.o: testsymtable.c symtable.h
	gcc217 -c testsymtable.c
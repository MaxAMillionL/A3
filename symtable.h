/*--------------------------------------------------------------------*/
/*                                                                    */
/* Header file for implementing the symtable functions from scratch   */
/* meant to learn the use of ADTs and debugging                       */
/*                                                                    */
/* Author: Maxwell Lloyd                                              */
/* Date: 3/25/25                                                      */
/*                                                                    */
/*--------------------------------------------------------------------*/


#ifndef STRING_INCLUDED
#define STRING_INCLUDED

#include <stddef.h>

/*--------------------------------------------------------------------*/

/* SymTable_T is a collection of nodes in a list format */
typedef struct SymTable* SymTable_T;

/*--------------------------------------------------------------------*/

/* Return a new SymTable object, or NULL if there is not enough memory  
   available */
SymTable_T SymTable_new(void);

/*--------------------------------------------------------------------*/

/* Free parameter oSymTable and all nodes, keys, and values associated 
   with it */
void SymTable_free(SymTable_T oSymTable);

/*--------------------------------------------------------------------*/

/* Finds the number of nodes in parameter oSymTable. Returns length of 
   oSymTable */
size_t SymTable_getLength(SymTable_T oSymTable);

/*--------------------------------------------------------------------*/

/* Adds a new elemenr to parameter symtable with value pvValue and key 
   pcKey. Returns 1 for success or 0 for failure */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, 
    const void *pvValue);

/*--------------------------------------------------------------------*/

/* Find if there is an element in parameter oSymTable with a binding 
   pcKey. If so, replace the value of pcKey with pvValue and return 
   pcKey's old value. Otherwise, the table remains unchanged and 
   returns NULL*/
void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, 
    const void *pvValue);

/*--------------------------------------------------------------------*/

/* Checks to see if there is a binding pcKey in parameter oSymTable. If 
   so, return 1 for success, otherwise return 0 for failure */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

/* Finds if there is a binding pcKey in parameter oSymTable and returns 
   its value. If pcKey does not exist, the table remains unchanged and 
   returns NULL */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

/*--------------------------------------------------------------------*/

/* Finds if there is a binding pcKey in parameter oSymTable, deletes 
   it, and returns its value. If pcKey does not exist, the table 
   remains unchanged and returns NULL */
void *SymTable_remove(SymTable_T oSymTable, const char *pcKey);

/*--------------------------------------------------------------------*/

/* Uses the function pfApply on every binding of the parameter oSymTable, using function pfApply(pcKey, pvValue, pvExtra) */
void SymTable_map(SymTable_T oSymTable, 
    void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra);


#endif
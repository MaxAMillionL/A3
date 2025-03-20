/*--------------------------------------------------------------------*/
/*                                                                    */
/* Header file for implementing the symtable functions from scratch   */
/* meant to learn the use of ADTs and debugging                       */
/*                                                                    */
/* Author: Maxwell Lloyd                                              */
/* Date: 3/25/25                                                      */
/*                                                                    */
/*--------------------------------------------------------------------*/



#include <stddef.h>
#include "symtable.h"

/*--------------------------------------------------------------------*/

/* Each item is stored in a SymTableNode to form a linked list */
struct SymTableNode{
   /* Key of each node */
   double dKey;

   /* Value of each node */
   double dValue;

   /* The address of the next StackNode. */
   struct StackNode *pNextNode;
};

/*--------------------------------------------------------------------*/

/* SymTable object is a manager pointing to the first node of a 
   SymTable_T object */
struct SymTable{
    /* First node of the list */
    struct SymTableNode *pFirstNode;
};

/*--------------------------------------------------------------------*/

SymTable_T SymTable_new(void){

}

/*--------------------------------------------------------------------*/

void SymTable_free(SymTable_T oSymTable){

}

/*--------------------------------------------------------------------*/

size_t SymTable_getLength(SymTable_T oSymTable){

}

/*--------------------------------------------------------------------*/

int SymTable_put(SymTable_T oSymTable, const char *pcKey, 
    const void *pvValue){
    
}

/*--------------------------------------------------------------------*/

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, 
    const void *pvValue){
    
}

/*--------------------------------------------------------------------*/

int SymTable_contains(SymTable_T oSymTable, const char *pcKey){

}

/*--------------------------------------------------------------------*/

void *SymTable_get(SymTable_T oSymTable, const char *pcKey){

}

/*--------------------------------------------------------------------*/

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey){

}

/*--------------------------------------------------------------------*/

void SymTable_map(SymTable_T oSymTable, void (*pfApply)
    (const char *pcKey, void *pvValue, void *pvExtra), 
    const void *pvExtra){
    
}
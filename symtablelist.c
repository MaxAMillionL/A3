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
   const void* pKey;

   /* Value of each node */
   const void* pValue;

   /* The address of the next SymTableNode. */
   struct SymTableNode *pNextNode;
};

/*--------------------------------------------------------------------*/

/* SymTable object is a manager pointing to the first node of a 
   SymTable_T object */
struct SymTable{
    /* First node of the list */
    struct SymTableNode *pFirstNode;
    size_t size;
};

/*--------------------------------------------------------------------*/

SymTable_T SymTable_new(void){
    SymTable_T oSymTable;

    oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
    if (oSymTable == NULL)
       return NULL;
 
    oSymTable->pFirstNode = NULL;
    oSymTable->size = 0;
    return oSymTable;
}

/*--------------------------------------------------------------------*/

void SymTable_free(SymTable_T oSymTable){
    struct SymTableNode *pCurrentNode;
    struct SymTableNode *pNextNode;
 
    assert(oSymTable != NULL);
 
    for (pCurrentNode = oSymTable->pFirstNode;
         pCurrentNode != NULL;
         pCurrentNode = pNextNode)
    {
       pNextNode = pCurrentNode->pNextNode;
       free(pCurrentNode);
    }

    free(oSymTable);
}

/*--------------------------------------------------------------------*/

size_t SymTable_getLength(SymTable_T oSymTable){
    struct SymTableNode *pCurrentNode;
    struct SymTableNode *pNextNode;
    size_t uLength = 0;

    for (pCurrentNode = oSymTable->pFirstNode;
        pCurrentNode != NULL;
        pCurrentNode = pNextNode)
   {
      pNextNode = pCurrentNode->pNextNode;
      uLength++;
   }

   return uLength;
}

/*--------------------------------------------------------------------*/

int SymTable_put(SymTable_T oSymTable, const char *pcKey, 
    const void *pvValue){
    struct SymTableNode *pNewNode;

    pNewNode = (struct SymTableNode*)malloc(sizeof(struct SymTableNode));
    if(pNewNode == NULL){
        return 0;
    }

    pNewNode->pKey = pcKey;
    pNewNode->pValue = pvValue;
    pNewNode->pNextNode = oSymTable->pFirstNode;
    oSymTable->pFirstNode = pNewNode;
    return 1;
}

/*--------------------------------------------------------------------*/

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, 
    const void *pvValue){
    struct SymTableNode *pCurrentNode;
    struct SymTableNode *pNextNode;
    int found = 0;

    pCurrentNode = oSymTable->pFirstNode;
    pNextNode = pCurrentNode->pNextNode;
    while(pCurrentNode != NULL && !found){
        if(pCurrentNode->pKey == pcKey){
            found = 1;
            const void* pOldValue = pCurrentNode->pValue;
            pCurrentNode->pValue = pvValue;
            return (void*) pOldValue;
        }
        pCurrentNode = pNextNode;
        pNextNode = pCurrentNode->pNextNode;
    }
    return NULL;
}

/*--------------------------------------------------------------------*/

int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    struct SymTableNode *pCurrentNode;
    struct SymTableNode *pNextNode;

    pCurrentNode = oSymTable->pFirstNode;
    pNextNode = pCurrentNode->pNextNode;
    while(pCurrentNode != NULL){
        if(pCurrentNode->pKey == pcKey){
            return 1;
        }
        pCurrentNode = pNextNode;
        pNextNode = pCurrentNode->pNextNode;
    }
    return 0;
}

/*--------------------------------------------------------------------*/

void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
    return 0;
}

/*--------------------------------------------------------------------*/

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    return 0;
}

/*--------------------------------------------------------------------*/

void SymTable_map(SymTable_T oSymTable, void (*pfApply)
    (const char *pcKey, void *pvValue, void *pvExtra), 
    const void *pvExtra){
        
}
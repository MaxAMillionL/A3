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
#include <assert.h>
#include <stdlib.h>
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
    assert(oSymTable != NULL);
    
    return oSymTable->size;
}

/*--------------------------------------------------------------------*/

int SymTable_put(SymTable_T oSymTable, const char *pcKey, 
    const void *pvValue){
    struct SymTableNode *pNewNode;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    pNewNode = (struct SymTableNode*)malloc(sizeof(struct SymTableNode));
    if(pNewNode == NULL){
        return 0;
    }

    if(SymTable_contains(oSymTable, pcKey)){
        return 0;
    }

    pNewNode->pKey = pcKey;
    pNewNode->pValue = pvValue;
    pNewNode->pNextNode = oSymTable->pFirstNode;
    oSymTable->pFirstNode = pNewNode;
    oSymTable->size++;
    return 1;
}

/*--------------------------------------------------------------------*/

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, 
    const void *pvValue){
    struct SymTableNode *pCurrentNode;
    const void* pOldValue;
    int found = 0;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    assert(pvValue != NULL);

    pCurrentNode = oSymTable->pFirstNode;
    while(pCurrentNode != NULL && !found){
        if(pCurrentNode->pKey == pcKey){
            found = 1;
            pOldValue = pCurrentNode->pValue;
            pCurrentNode->pValue = pvValue;
            return (void*) pOldValue;
        }
        pCurrentNode = pCurrentNode->pNextNode;
    }
    return NULL;
}

/*--------------------------------------------------------------------*/

int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    struct SymTableNode *pCurrentNode;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    pCurrentNode = oSymTable->pFirstNode;
    while(pCurrentNode != NULL){
        if(pCurrentNode->pKey == pcKey){
            return 1;
        }
        pCurrentNode = pCurrentNode->pNextNode;
    }
    return 0;
}

/*--------------------------------------------------------------------*/

void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
    struct SymTableNode *pCurrentNode;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    pCurrentNode = oSymTable->pFirstNode;
    while(pCurrentNode != NULL){
        if(pCurrentNode->pKey == pcKey){
            return (void*)(pCurrentNode->pValue);
        }
        pCurrentNode = pCurrentNode->pNextNode;
    }
    return NULL;
}

/*--------------------------------------------------------------------*/

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    struct SymTableNode *pPrevNode;
    struct SymTableNode *pCurrentNode;
    const void* pOldValue;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    pCurrentNode = oSymTable->pFirstNode;
    pPrevNode = NULL;
    while(pCurrentNode != NULL){
        if(pCurrentNode->pKey == pcKey){
            pOldValue = pCurrentNode->pValue;
            if(pPrevNode == NULL){
                oSymTable->pFirstNode = pCurrentNode->pNextNode;
            }
            else{
                pPrevNode->pNextNode = pCurrentNode->pNextNode;
            }
            free(pCurrentNode);
            oSymTable->size--;
            return (void*) pOldValue;
        }
        pPrevNode = pCurrentNode;
        pCurrentNode = pCurrentNode->pNextNode;
    }
    return NULL;
}

/*--------------------------------------------------------------------*/

void SymTable_map(SymTable_T oSymTable, void (*pfApply)
    (const char *pcKey, void *pvValue, void *pvExtra), 
    const void *pvExtra){
    struct SymTableNode *pCurrentNode;

    assert(oSymTable != NULL);
    assert(pfApply != NULL);

    pCurrentNode = oSymTable->pFirstNode;
    while(pCurrentNode != NULL){
        (*pfApply)(pCurrentNode->pKey, pCurrentNode->pValue, pvExtra);
        pCurrentNode = pCurrentNode->pNextNode;
    }
}
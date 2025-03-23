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
#include <string.h>
#include <stdio.h>
#include "symtable.h"

/*--------------------------------------------------------------------*/

/* Each item is stored in a SymTableNode to form a linked list */
struct SymTableNode{
   /* Key of each node */
   const char* pKey;

   /* Value of each node */
   const void* pValue;

   /* The address of the next SymTableNode. */
   struct SymTableNode *pNextNode;
};

/*--------------------------------------------------------------------*/
struct SymTableBucket{
    /* Pointer to a linked list for this bucket */
    struct SymTableNode *pFirstBucketNode;
 };

/*--------------------------------------------------------------------*/

/* SymTable object is a manager pointing to the first node of a 
   SymTable_T object */
struct SymTable{
    /* First node of the list */
    struct SymTableBucket *pFirstBucket;

    /* size of the entire symtable */
    size_t size;

    /* limit of buckets until expansion */
    size_t limit;
};

/*--------------------------------------------------------------------*/

/* Return a hash code for pcKey that is between 0 and uBucketCount-1,
   inclusive. */

static size_t SymTable_hash(const char *pcKey, size_t uBucketCount)
{
    const size_t HASH_MULTIPLIER = 65599;
    size_t u;
    size_t uHash = 0;

    assert(pcKey != NULL);

    for (u = 0; pcKey[u] != '\0'; u++)
        uHash = uHash * HASH_MULTIPLIER + (size_t)pcKey[u];

    return uHash % uBucketCount;
}

/*--------------------------------------------------------------------*/

/* Resize the list of buckets in oSymTable to the next iteration. */

static struct SymTableBucket* SymTable_resize(SymTable_T oSymTable)
{
    assert(oSymTable != NULL);
    
    int sizes[8] = {509, 1021, 2039, 4093, 8191, 16381, 32749, 65521};
    
    return oSymTable->pFirstBucket;
}
   
/*--------------------------------------------------------------------*/

SymTable_T SymTable_new(void){
    SymTable_T oSymTable;

    oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
    if (oSymTable == NULL)
       return NULL;
 
    /* 509 elements for a new hash table */
    oSymTable->pFirstBucket = calloc(509, sizeof(struct SymTableBucket));
    if (oSymTable->pFirstBucket == NULL)
        return NULL;

    oSymTable->size = 0;
    oSymTable->limit = 509;
    return oSymTable;
}

/*--------------------------------------------------------------------*/

void SymTable_free(SymTable_T oSymTable){
    struct SymTableBucket *pCurrentBucket;
    struct SymTableNode *pCurrentNode;
    struct SymTableNode *pNextNode;
    size_t counter;
 
    assert(oSymTable != NULL);

    counter = 0;
    pCurrentBucket = oSymTable->pFirstBucket;
    while(counter < oSymTable->limit){
        /* Free the linked list associated with the bucket*/
        if(pCurrentBucket->pFirstBucketNode != NULL){
            for (pCurrentNode = pCurrentBucket->pFirstBucketNode;
                pCurrentNode != NULL;
                pCurrentNode = pNextNode)
            {
                printf("Node: %zu\n", (size_t)pCurrentNode);
                fflush(stdout);
                pNextNode = pCurrentNode->pNextNode;
                free((void*)pCurrentNode->pKey);
                free(pCurrentNode);
                printf("success\n");
                fflush(stdout);

                
            }
        }
        printf("Bucket: %zu\n", (size_t)pCurrentBucket);
        fflush(stdout);
        free(pCurrentBucket);
        printf("success\n");
        fflush(stdout);
        
        pCurrentBucket++;
        counter++;
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
    char *pKey;
    size_t bucketNumber;
    size_t strLength;
    struct SymTableNode *pBucket;
    struct SymTableNode *pNewNode;
    struct SymTableNode *pOldNode;
    struct SymTableBucket *pbCurrent;
    

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    if(SymTable_contains(oSymTable, pcKey)){
        return 0;
    }

    pNewNode = (struct SymTableNode*)malloc(sizeof(struct SymTableNode));
    if(pNewNode == NULL){
        return 0;
    }

    /* Defensive copy */
    strLength = strlen(pcKey) + 1;
    pKey = (char*) malloc(strLength * sizeof(char));
    if(pKey == NULL){
        free(pNewNode);
        return 0;
    }
    strcpy(pKey, pcKey);

    /* Find position of the bucket assocaited with the hash */
    bucketNumber = SymTable_hash(pKey, oSymTable->limit);
    pbCurrent = oSymTable->pFirstBucket;
    while((size_t)(pbCurrent - oSymTable->pFirstBucket) != bucketNumber){
        pbCurrent++;
    }

    pNewNode->pKey = pKey;
    pNewNode->pValue = pvValue;

    /* Add node to first bucket if empty, or start of linked list otherwise */
    if(pbCurrent->pFirstBucketNode == NULL){
        pbCurrent->pFirstBucketNode = pNewNode;
    }
    else{
        pOldNode = pbCurrent->pFirstBucketNode;
        pbCurrent->pFirstBucketNode = pNewNode;
        pNewNode->pNextNode = pOldNode;
    }
    oSymTable->size++;

    /* Resize if size exceeds limit, but only below maximum */
    if(oSymTable->limit != 65521 && oSymTable->size > oSymTable->limit){
        SymTable_resize(oSymTable);
    }


    return 1;
}

/*--------------------------------------------------------------------*/

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, 
    const void *pvValue){
    struct SymTableNode *pCurrentNode;
    struct SymTableBucket *pbCurrent;
    const void* pOldValue;
    size_t bucketNumber;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    /* Find position of the bucket assocaited with the hash */
    bucketNumber = SymTable_hash(pcKey, oSymTable->limit);
    pbCurrent = oSymTable->pFirstBucket;
    while((size_t)(pbCurrent - oSymTable->pFirstBucket) != bucketNumber){
        pbCurrent++;
    }

    pCurrentNode = pbCurrent->pFirstBucketNode;
    while(pCurrentNode != NULL){
        if(strcmp(pCurrentNode->pKey, pcKey) == 0){
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
    struct SymTableBucket *pbCurrent;
    size_t bucketNumber;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    /* Find position of the bucket assocaited with the hash */
    bucketNumber = SymTable_hash(pcKey, oSymTable->limit);
    pbCurrent = oSymTable->pFirstBucket;
    while((size_t)(pbCurrent - oSymTable->pFirstBucket) != bucketNumber){
        pbCurrent++;
    }

    pCurrentNode = pbCurrent->pFirstBucketNode;
    while(pCurrentNode != NULL){
        if(strcmp(pCurrentNode->pKey, pcKey) == 0){
            return 1;
        }
        pCurrentNode = pCurrentNode->pNextNode;
    }
    return 0;
}

/*--------------------------------------------------------------------*/

void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
    struct SymTableNode *pCurrentNode;
    struct SymTableBucket *pbCurrent;
    size_t bucketNumber;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    /* Find position of the bucket assocaited with the hash */
    bucketNumber = SymTable_hash(pcKey, oSymTable->limit);
    pbCurrent = oSymTable->pFirstBucket;
    while((size_t)(pbCurrent - oSymTable->pFirstBucket) != bucketNumber){
        pbCurrent++;
    }

    pCurrentNode = pbCurrent->pFirstBucketNode;
    while(pCurrentNode != NULL){
        if(strcmp(pCurrentNode->pKey, pcKey) == 0){
            return (void*)(pCurrentNode->pValue);
        }
        pCurrentNode = pCurrentNode->pNextNode;
    }
    return 0;
}

/*--------------------------------------------------------------------*/

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    struct SymTableNode *pPrevNode;
    struct SymTableNode *pCurrentNode;
    struct SymTableBucket *pbCurrent;
    size_t bucketNumber;
    const void* pOldValue;

    assert(oSymTable != NULL);
    assert(pcKey != NULL);

    /* Find position of the bucket assocaited with the hash */
    bucketNumber = SymTable_hash(pcKey, oSymTable->limit);
    pbCurrent = oSymTable->pFirstBucket;
    while((size_t)(pbCurrent - oSymTable->pFirstBucket) != bucketNumber){
        pbCurrent++;
    }

    pCurrentNode = pbCurrent->pFirstBucketNode;
    pPrevNode = NULL;
    while(pCurrentNode != NULL){
        if(strcmp(pCurrentNode->pKey, pcKey) == 0){
            pOldValue = pCurrentNode->pValue;
            if(pPrevNode == NULL){
                pbCurrent->pFirstBucketNode = pCurrentNode->pNextNode;
            }
            else{
                pPrevNode->pNextNode = pCurrentNode->pNextNode;
            }
            free((void*)pCurrentNode->pKey);
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
    struct SymTableBucket *pCurrentBucket;

    assert(oSymTable != NULL);
    assert(pfApply != NULL);

    for(pCurrentBucket = oSymTable->pFirstBucket;
        (size_t)(pCurrentBucket - oSymTable->pFirstBucket) 
        <= oSymTable->limit;
        pCurrentBucket++)
    {
        /* Free the linked list associated with the bucket*/
        if(pCurrentBucket->pFirstBucketNode != NULL){
            for (pCurrentNode = pCurrentBucket->pFirstBucketNode;
                pCurrentNode != NULL;
                pCurrentNode++)
            {
                (*pfApply)(pCurrentNode->pKey, (void*)pCurrentNode->pValue, (void*) pvExtra);
                pCurrentNode = pCurrentNode->pNextNode;
            }
        }
    }
}
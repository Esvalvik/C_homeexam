

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

static NODE *CreateNode (char* pPath, void* pValue)
{
   NODE *pThis = malloc (sizeof(LIST) + iSze);
   if (pThis != NULL) {
      memset (pThis, 0, sizeof(LIST) + iSze);
      pthis->
      memcpy (pThis->byBuf, pvData, iSze);
   }
   return pThis;
}


int InsertInList (LIST **ppHead, void *pvData, int iSze)
{
   int iRc = ERROR;
   LIST *pThis = CreateNode (pvData, iSze);
   if (pThis != NULL) {
      pThis->pNext = *ppHead;
      *ppHead = pThis;
      iRc = OK;
   }
   return iRc;
}

int AddToList (LIST **ppHead, void *pvData, int iSze)
{
   int iRc = ERROR;
   LIST *pThis = CreateNode (pvData, iSze);
   if (pThis != NULL) {
      if (*ppHead == NULL) {
         *ppHead = pThis;
         iRc = OK;
      }
      else {
         LIST *pList = *ppHead;
         while (pList->pNext != NULL) {
            pList = pList->pNext;
         }
         pList->pNext = pThis;
         iRc = OK;
      }
   }
   return iRc;
}

int RemoveFromList (LIST **ppHead, LIST *pToDelete)
{
   int iRc = ERROR;
   LIST *pThis = NULL;
   LIST *pPrev = NULL;

   if (*ppHead == pToDelete) {
      (*ppHead = pToDelete->pNext);
      iRc = OK;
   }
   else {
      pThis = *ppHead;
      while (pThis != NULL) {
         if (pThis == pToDelete) {
            pPrev->pNext = pThis->pNext;
            iRc = OK;
            break;
         }
         pPrev = pThis;
         pThis = pThis->pNext;
      }
   }
   if (iRc == OK) free (pToDelete);
   return iRc;
}
